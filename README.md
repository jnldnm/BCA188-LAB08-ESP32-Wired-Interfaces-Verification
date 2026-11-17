# ESP32 Wired Interfaces Verification: UART, I²C, and SPI

**Subject:** BCA188 - Programming for Internet of Things   
**Laboratory Activity:** Verification of the Three Wired Interfaces on an ESP32 (UART, I²C, and SPI)

## Introduction

This laboratory activity examines three wired communication interfaces supported by the ESP32-WROOM-32: Universal Asynchronous Receiver/Transmitter (UART), Inter-Integrated Circuit (I²C), and Serial Peripheral Interface (SPI). The project uses separate Arduino sketches to demonstrate UART and SPI loopback communication and I²C device-address detection.

The implementation uses GPIO-based connections and the ESP32 Arduino Core communication libraries. The activity also illustrates the relationship between serial baud-rate settings and readable USB Serial Monitor output.

## Communication Interfaces

| Interface | Demonstration | ESP32 GPIO assignments |
|---|---|---|
| UART2 | TX-to-RX loopback using `PING` data | TX: GPIO 17; RX: GPIO 16 |
| I²C | Device-address scanning | SDA: GPIO 21; SCL: GPIO 22 |
| SPI | MOSI-to-MISO loopback using byte `0xA5` | SCK: GPIO 18; MOSI: GPIO 23; MISO: GPIO 19; CS: GPIO 25 |

These assignments are intended for a classic ESP32-WROOM-32 DevKit. The board pinout and electrical requirements of any connected I²C module determine the appropriate physical connections.

## Project Files

```text
BCA188-LAB08-ESP32-Wired-Interfaces-Verification/
├── README.md
├── ACTIVITY-ANSWERS.md
├── Documentation/
└── SourceCode/
    ├── uart_loopback/
    │   └── uart_loopback.ino
    ├── i2c_scanner/
    │   └── i2c_scanner.ino
    └── spi_loopback/
        └── spi_loopback.ino
```

The `SourceCode` directory contains the three interface demonstrations. `Documentation` contains the project's supporting visual evidence. The laboratory questions and technical explanations are presented in [ACTIVITY-ANSWERS.md](ACTIVITY-ANSWERS.md).

## Development Platform

- **Microcontroller:** ESP32-WROOM-32 development board
- **Development environment:** Arduino IDE
- **Framework:** ESP32 Arduino Core
- **Communication libraries:** `HardwareSerial` / `Serial`, `Wire`, and `SPI`
- **Programming language:** C++ (Arduino framework)

## Summary

The project demonstrates the different communication characteristics of UART, I²C, and SPI. UART transfers data asynchronously using configured serial parameters, I²C identifies devices through bus addresses, and SPI transfers data synchronously using a clock and chip-select signal. Together, these demonstrations provide a practical comparison of the three interfaces.
