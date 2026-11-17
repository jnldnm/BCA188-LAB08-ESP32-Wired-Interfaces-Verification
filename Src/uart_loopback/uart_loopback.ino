
#include <Arduino.h>

// UART2 pin configuration
#define UART_TX_PIN 17
#define UART_RX_PIN 16

// USB Serial baud rate
#define USB_BAUD_RATE 115200

// UART2 baud rate
#define UART_BAUD_RATE 9600

unsigned long previousMillis = 0;
const unsigned long interval = 1000;

// Buffer for received UART characters
char rxBuffer[4];
int rxIndex = 0;

void setup() {
  // Initialize USB Serial
  Serial.begin(USB_BAUD_RATE);

  // Initialize UART2 using the selected GPIO pins
  Serial2.begin(
    UART_BAUD_RATE,
    SERIAL_8N1,
    UART_RX_PIN,
    UART_TX_PIN
  );

  Serial.println("UART2 Loopback Test Started");
  Serial.println("Connect GPIO 17 (TX) to GPIO 16 (RX)");
}

void loop() {

  // Send PING every second
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    Serial2.write("PING");

    Serial.println("Sent: PING");
  }

  // Read received UART data
  while (Serial2.available() > 0) {

    char receivedChar = Serial2.read();

    // Store each received character
    rxBuffer[rxIndex] = receivedChar;
    rxIndex++;

    // Display every four received bytes
    if (rxIndex == 4) {

      Serial.print("Received: ");

      for (int i = 0; i < 4; i++) {
        Serial.print(rxBuffer[i]);
      }

      Serial.println();

      rxIndex = 0;
    }
  }
}
