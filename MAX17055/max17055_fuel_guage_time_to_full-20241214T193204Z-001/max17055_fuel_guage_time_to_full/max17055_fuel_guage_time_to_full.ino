#include "Wire.h"
#include <Thanos_MAX17055.h>

Thanos_MAX17055 MAX17055;

// MAX17055 valiables
float cellVoltage = 0;
float current_mA = 0;
float Avg_current_mA = 0;
float stateOfCharge = 0;
float FullRepCap = 0;
float RepCap = 0;
float DieTemp = 0;
float cellTTE = 0;
float cellTTF = 0;
float prev_soc = 0;

void setup() {
  byte error, address;
  int nDevices;

  Serial.begin(9600);  // Initialize hardware serial port, pins 0/1
 
  Wire.begin();
  
  //Initialize the Max17055 enter the capacity of the battery that we are going to use.
  MAX17055.begin(5200);
  Serial.println(" MAX17055 started\r");
  Serial.println("Measuring voltage and current with MAX17055 ...");


} 

void loop() {
  cellVoltage = MAX17055.getVoltageCell();
  current_mA = MAX17055.getCurrent_mA();
  Avg_current_mA = MAX17055.getAvgCurrent_mA();
  stateOfCharge = MAX17055.getRepSOC();
  FullRepCap = MAX17055.getFullRepCap();
  RepCap = MAX17055.getRepCap();
  DieTemp = MAX17055.getTemp();
  cellTTE = MAX17055.getTTE();
  cellTTF = MAX17055.getTTF();
  uint16_t cellVoltagefix = cellVoltage;

  

  Serial.print("SOC ");
  Serial.print(stateOfCharge);   // print the reading High Byte only percent value
  Serial.print("%, ");
  Serial.print(cellVoltagefix);   // print the reading
  Serial.print("mV, ");
  Serial.print(" CAP ");
  Serial.print(RepCap);   // print the readin
  Serial.print("mAh of ");
  Serial.print(FullRepCap);   // print the reading
  Serial.print("mAh, ");
  Serial.print(DieTemp);  // print the reading
  Serial.print("C,  ");
  Serial.print("Time to [Empty ");
  Serial.print(cellTTE); // print the reading
  Serial.print("hrs] - [Full ");
  Serial.print(cellTTF); // print the reading
  Serial.println("hrs]  ");

  prev_soc = stateOfCharge;
}
