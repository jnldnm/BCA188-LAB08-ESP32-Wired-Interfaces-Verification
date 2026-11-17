
#include <Arduino.h>
#include <Wire.h>

// I2C pin configuration
#define SDA_PIN 21
#define SCL_PIN 22

void setup() {

  // Initialize USB Serial
  Serial.begin(115200);

  delay(1000);

  Serial.println("I2C Scanner Started");

  // Initialize I2C using the assigned GPIO pins
  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.println("Scanning I2C devices...");

  byte devicesFound = 0;

  // Scan all valid 7-bit I2C addresses
  for (byte address = 0x01; address <= 0x7E; address++) {

    Wire.beginTransmission(address);

    byte error = Wire.endTransmission();

    if (error == 0) {

      Serial.print("Found device at 0x");

      if (address < 0x10) {
        Serial.print("0");
      }

      Serial.println(address, HEX);

      devicesFound++;
    }
  }

  // Display the scan result
  if (devicesFound == 0) {
    Serial.println("No I2C devices found");
  }
  else {
    Serial.print("Scan complete. Devices found: ");
    Serial.println(devicesFound);
  }
}

void loop() {
  // The scanner runs once during startup.
}
