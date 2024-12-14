const int LOADCELL_DOUT_PIN = 3; // DT
const int LOADCELL_SCK_PIN = 2;  // SCK

long tare_value = 0;  // Tare offset
float calibration_factor = 1.0;  // Calibration factor to be determined

void setup() {
  Serial.begin(9600);
  pinMode(LOADCELL_DOUT_PIN, INPUT);
  pinMode(LOADCELL_SCK_PIN, OUTPUT);

  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from the scale");
  delay(2000);
  Serial.println("Taring... Remove any weights from the scale.");
  delay(1000);
  
  tare_value = readAverage(10);  // Get a baseline reading
  Serial.print("Tare value: "); // This can be used to remove the zero offset
  Serial.println(tare_value);

  Serial.println("Place a known weight on the scale");
  delay(2000);
}

void loop() {
  if (Serial.available()) {
    char temp = Serial.read();
    if (temp == 'c') {  // 'c' to calibrate
      Serial.println("Calibrating...");
      Serial.println("Place a known weight on the scale now.");
      delay(2000);  // Wait for a stable reading

      float known_weight = 146.0;  // Replace with your known weight value
      long raw_value = readAverage(10) - tare_value;  // Get the raw value, adjusted for tare
      calibration_factor = raw_value / known_weight;  // Calculate the calibration factor
  Serial.print("RAW");
      Serial.println(raw_value);
      Serial.print("Calibration factor: ");
      Serial.println(calibration_factor);
    }
  }

  // To get a calibrated reading, use the calibration factor
  long raw_value = readAverage(1000) - tare_value;
  float weight = raw_value / calibration_factor;
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" grams");

  delay(1000);
}

long readHX711() {
  while (digitalRead(LOADCELL_DOUT_PIN) == HIGH);  // Wait for the HX711 to become ready

  long count = 0;
  for (int i = 0; i < 24; i++) {
    digitalWrite(LOADCELL_SCK_PIN, HIGH);
    delayMicroseconds(1);
    count = count << 1;
    digitalWrite(LOADCELL_SCK_PIN, LOW);
    if (digitalRead(LOADCELL_DOUT_PIN) == HIGH) {
      count++;
    }
    delayMicroseconds(1);
  }

  // Set the channel and gain factor (32 for Channel B)
  digitalWrite(LOADCELL_SCK_PIN, HIGH);
  delayMicroseconds(1);
  digitalWrite(LOADCELL_SCK_PIN, LOW);
  delayMicroseconds(1);

  // Convert 24-bit 2's complement to 32-bit signed
  if (count & 0x800000) {
    count |= ~0xFFFFFF;
  }

  return count;
}

long readAverage(int times) {
  long sum = 0;
  for (int i = 0; i < times; i++) {
    sum += readHX711();
  }
  return sum / times;
}
