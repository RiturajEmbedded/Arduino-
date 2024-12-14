#include <Adafruit_GFX.h>        // Core graphics library
#include <Adafruit_SSD1351.h>    // Library for SSD1351 OLED
#include <SPI.h>                 // SPI communication library

// Define pins for the OLED display
#define OLED_CS     10    // Chip Select pin
#define OLED_DC     9     // Data/Command pin
#define OLED_RST    8     // Reset pin

// Initialize the OLED display (128x128 resolution)
Adafruit_SSD1351 display = Adafruit_SSD1351(128, 128, &SPI, OLED_CS, OLED_DC, OLED_RST);

void setup() {
  // Initialize the display
  display.begin();
  display.fillScreen(0x001F);  // Clear the screen with black (0x0000)
  
  // Set text properties
  display.setTextColor(0x0000);           // Set text color to white (0xFFFF)
  display.setTextSize(3);                 // Set text size
  
  // Display the label "Voltage"
  display.setCursor(0, 0);                // Set cursor position
  display.println("Voltage:");
  
  // Display the large number
  display.setTextSize(2);                 // Text size can be adjusted to fit the screen
  display.setCursor(0, 70);               // Set cursor for the number
  display.println("243");
}

void loop() {
  // No action in the loop for now
}
