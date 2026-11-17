
#include <Arduino.h>
#include <SPI.h>

// SPI pin configuration
#define SCK_PIN 18
#define MISO_PIN 19
#define MOSI_PIN 23
#define CS_PIN 25

// SPI clock frequency
#define SPI_FREQUENCY 1000000

// SPI configuration:
// MSB first, SPI Mode 0
SPISettings spiSettings(
  SPI_FREQUENCY,
  MSBFIRST,
  SPI_MODE0
);

void setup() {

  // Initialize USB Serial
  Serial.begin(115200);

  delay(1000);

  Serial.println("SPI Loopback Test Started");

  // Configure CS as output
  pinMode(CS_PIN, OUTPUT);

  // Keep SPI device deselected
  digitalWrite(CS_PIN, HIGH);

  // Initialize SPI with custom pins
  SPI.begin(
    SCK_PIN,
    MISO_PIN,
    MOSI_PIN,
    CS_PIN
  );
}

void loop() {

  byte transmittedData = 0xA5;
  byte receivedData;

  // Configure SPI transaction
  SPI.beginTransaction(spiSettings);

  // Select the SPI device
  digitalWrite(CS_PIN, LOW);

  // Send and receive one byte
  receivedData = SPI.transfer(transmittedData);

  // Deselect the SPI device
  digitalWrite(CS_PIN, HIGH);

  // End SPI transaction
  SPI.endTransaction();

  // Display transmitted and received values
  Serial.print("Sent 0x");
  Serial.print(transmittedData, HEX);

  Serial.print(", received 0x");

  if (receivedData < 0x10) {
    Serial.print("0");
  }

  Serial.println(receivedData, HEX);

  delay(1000);
}
