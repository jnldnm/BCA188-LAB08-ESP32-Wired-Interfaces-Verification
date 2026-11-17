# Laboratory Activity Answers

**Subject:** BCA188  
**Laboratory Activity:** Verification of the Three Wired Interfaces on an ESP32 (UART, I²C, and SPI)

## Introduction

This document presents the pin assignments and conceptual answers for the ESP32 wired-interface verification activity. It covers UART, I²C, and SPI communication, including the role of loopback connections, I²C addressing, SPI chip selection, and serial baud-rate matching.

## 1. Pin Assignment Table

The following GPIO assignments are intended for a classic ESP32-WROOM-32 DevKit.

| Signal | GPIO |
|---|---:|
| UART TX | 17 |
| UART RX | 16 |
| I²C SDA | 21 |
| I²C SCL | 22 |
| SPI SCK | 18 |
| SPI MOSI | 23 |
| SPI MISO | 19 |
| SPI CS | 25 |

## 2. Communication Test Summary

| Test condition | Communication behavior |
|---|---|
| UART with TX-to-RX loopback | Data transmitted through GPIO 17 is returned to GPIO 16. The received data should match the transmitted `PING` message. |
| UART without loopback | The transmitted data is not directly returned to the receiver. An unconnected RX input may produce unstable or random readings. |
| I²C with a connected device | The scanner reports the address of each I²C device that acknowledges on the bus. |
| I²C without a connected device | No device address is reported if no other I²C device is present. |
| SPI with MOSI-to-MISO loopback | The byte transmitted on MOSI is returned through MISO. The received byte should match `0xA5`. |
| SPI without loopback | The received value is not guaranteed to match `0xA5` because MISO is not connected to the transmitted data. |
| USB Serial baud-rate mismatch | Output may appear corrupted or unreadable when the Serial Monitor baud rate differs from the sketch's USB Serial baud rate. |
| Matching USB Serial baud rates | Output is readable when the sketch and Serial Monitor use the same baud rate. |

## 3. Activity Questions

### 1. Why does UART need both sides to use the same baud rate, while SPI uses a clock line?

UART is asynchronous, so the transmitter and receiver must use the same baud rate to interpret the timing of each bit correctly. SPI is synchronous because the controller supplies a clock signal that determines when data is sampled. Therefore, SPI uses the clock signal to coordinate data transfer rather than relying on both sides to independently match a baud-rate setting.

### 2. Why can two devices with the same address not share one I²C bus?

Each I²C device on a bus needs a unique address so the controller can identify the intended device. If two devices have the same address, both may respond to the same communication request. This creates an address conflict and can cause unreliable or ambiguous communication.

### 3. Why is CS set HIGH between SPI transfers?

In this activity, Chip Select (CS) is active LOW. Setting CS HIGH deactivates the selected SPI device between transfers. This separates one transaction from another and allows the controller to select the device again by setting CS LOW for the next transfer.

## 4. Wiring Reference

### UART loopback

| ESP32 signal | Connection |
|---|---|
| UART TX | GPIO 17 |
| UART RX | GPIO 16 |
| Loopback | GPIO 17 (TX) connected to GPIO 16 (RX) |

### I²C device

| I²C module pin | ESP32 connection |
|---|---|
| SDA | GPIO 21 |
| SCL | GPIO 22 |
| VCC/VIN | Supply compatible with the module |
| GND | GND |

### SPI loopback

| SPI signal | ESP32 connection |
|---|---|
| SCK | GPIO 18 |
| MOSI | GPIO 23 |
| MISO | GPIO 19 |
| CS | GPIO 25 |
| Loopback | GPIO 23 (MOSI) connected to GPIO 19 (MISO) |

## 5. References

- Espressif Systems, [ESP32-WROOM-32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf).
- Espressif Systems, [Arduino ESP32 Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/).
- Arduino, [Wire Library](https://docs.arduino.cc/language-reference/en/functions/communication/wire/).
- Arduino, [SPI Library](https://docs.arduino.cc/language-reference/en/functions/communication/SPI/).
- Arduino, [Serial Communication](https://docs.arduino.cc/language-reference/en/functions/communication/serial/).
