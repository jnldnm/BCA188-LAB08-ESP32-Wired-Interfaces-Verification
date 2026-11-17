# ESP32 Wired Interfaces Verification: UART, I²C, and SPI

## 1. About the Project

This laboratory project verifies three wired communication interfaces available on an ESP32-WROOM-32 development board: UART, I²C, and SPI. Three independent Arduino sketches are used to test each interface.

- **UART loopback:** Sends `PING` through `Serial2` and receives it through a jumper connecting TX to RX.
- **I²C scanner:** Scans addresses `0x01` through `0x7E` and reports devices that acknowledge.
- **SPI loopback:** Sends `0xA5` over SPI and reads the byte back through a jumper connecting MOSI to MISO.

The tests compare behavior with and without the relevant jumper or I²C module. A final baud-rate test demonstrates why the USB Serial Monitor must use the same baud rate as `Serial`.

> **Evidence status:** This README describes the intended implementation. Replace the pending-result placeholders with actual observations after performing the tests. Do not treat expected values as measured results.

## 2. Objectives

1. Identify suitable ESP32 GPIO pins for UART, I²C, and SPI.
2. Configure UART2 and verify transmission/reception with a TX-to-RX loopback.
3. Use the ESP32 `Wire` library to scan for I²C devices.
4. Configure SPI and verify transmission/reception with a MOSI-to-MISO loopback.
5. Compare connected and disconnected test conditions.
6. Demonstrate the effect of a mismatch between the USB Serial baud rate and the Serial Monitor baud rate.
7. Document the wiring, source code, Serial Monitor output, and experimental observations.

## 3. Technologies and Requirements

### Software

| Technology | Purpose |
|---|---|
| Arduino IDE | Edit, compile, and upload each sketch |
| ESP32 Arduino Core | Provides ESP32 board support and communication APIs |
| Serial Monitor | Displays test output at the configured USB Serial baud rate |
| GitHub Desktop | Commits and pushes the project without requiring Git commands |
| Windows File Explorer | Organizes the repository and evidence files |

### Hardware

| Component | Purpose |
|---|---|
| ESP32 DevKit using ESP32-WROOM-32 | Microcontroller under test |
| USB data cable | Powers/programs the board and provides USB Serial |
| Breadboard and jumper wires | Makes the loopback and module connections |
| One I²C module (OLED or BME280/BMP280) | Responds to the I²C scanner |
| Computer | Runs the IDE and Serial Monitor |

### Libraries

- `Arduino.h` — core Arduino functions.
- `Wire.h` — I²C bus functions.
- `SPI.h` — SPI bus functions.

These are provided by the ESP32 Arduino Core. No third-party library is needed for the scanner or loopback tests.

## 4. Project Structure

```text
ESP32-Wired-Interfaces-Verification/
│
├── README.md
├── ACTIVITY-ANSWERS.md
│
├── Documentation/
│   ├── screenshot-01-pin-configuration.png
│   ├── screenshot-02-uart-wiring.png
│   ├── screenshot-03-uart-loopback.png
│   ├── screenshot-04-uart-no-loopback.png
│   ├── screenshot-05-i2c-wiring.png
│   ├── screenshot-06-i2c-with-module.png
│   ├── screenshot-07-i2c-without-module.png
│   ├── screenshot-08-spi-wiring.png
│   ├── screenshot-09-spi-loopback.png
│   ├── screenshot-10-spi-no-loopback.png
│   ├── screenshot-11-baud-mismatch.png
│   └── screenshot-12-baud-match.png
│
└── SourceCode/
    ├── uart_loopback/
    │   └── uart_loopback.ino
    ├── i2c_scanner/
    │   └── i2c_scanner.ino
    └── spi_loopback/
        └── spi_loopback.ino
```

`Documentation/` stores the labeled wiring evidence and Serial Monitor captures. Each source folder contains one independent Arduino sketch. The two Markdown files are stored at the repository root.

## 5. Installation and Setup

1. Install the Arduino IDE from [arduino.cc/en/software](https://www.arduino.cc/en/software).
2. Install ESP32 board support using the Arduino IDE Boards Manager. Search for **esp32** and install **esp32 by Espressif Systems**.
3. Connect the ESP32 using a USB data cable.
4. In **Tools → Board**, select the matching ESP32 Dev Module/DevKit board profile appropriate for the WROOM-32 board.
5. In **Tools → Port**, select the COM port assigned to the ESP32.
6. Open the Serial Monitor and select **115200 baud** for the normal tests.
7. Create/open each `.ino` sketch separately, matching its folder and filename.

Board menu labels can vary by installed ESP32 core version. Confirm the selected profile and port before uploading.

## 6. Pin Configuration and Wiring

The following is a suggested pin assignment for a classic ESP32-WROOM-32 DevKit. Confirm the board's actual pinout before connecting wires. The pins are distinct, avoid GPIO 6–11, and do not use input-only GPIO 34–39 for outputs.

| Signal | GPIO used |
|---|---:|
| UART TX | 17 |
| UART RX | 16 |
| I²C SDA | 21 |
| I²C SCL | 22 |
| SPI SCK | 18 |
| SPI MOSI | 23 |
| SPI MISO | 19 |
| SPI CS | 25 |

### UART wiring

- GPIO 17 (UART TX) → GPIO 16 (UART RX), using one jumper.
- Connect the ESP32 to the computer by USB for power, programming, and USB Serial output.

### I²C wiring

| I²C module pin | ESP32 connection |
|---|---|
| SDA | GPIO 21 |
| SCL | GPIO 22 |
| VCC/VIN | 3V3, only if compatible with the module |
| GND | GND |

Remove the I²C module for the no-module scan. Check the module's pin labels and voltage specifications before powering it.

### SPI wiring

- GPIO 18: SCK
- GPIO 23: MOSI
- GPIO 19: MISO
- GPIO 25: CS
- Connect GPIO 23 (MOSI) to GPIO 19 (MISO) using one jumper.
- SCK and CS connect to their assigned ESP32 pins; they are not jumpered to each other.

### Wiring diagram to add

Create a hand-drawn or digital diagram, or take a clearly labeled photo of the physical build. Show each signal name and GPIO number. For the I²C setup, show SDA, SCL, VCC, and GND. Save the evidence as the wiring screenshots listed in Section 7.

## 7. Implementation and Procedure

### Phase 1 — Prepare the project and pin assignments

1. Create the repository folder and the folder structure shown above.
2. Confirm that the board uses an ESP32-WROOM-32 module.
3. Check the board pinout and confirm the proposed GPIO assignments.
4. Write the pin assignments in the activity answer table.
5. Keep USB disconnected whenever changing any wire.

**Screenshot reminder — `Documentation/screenshot-01-pin-configuration.png`**

Capture the completed pin table and, if possible, the board pinout used to verify the GPIO choices. This belongs in Project Documentation.

**Checkpoint:** All eight signals have distinct GPIO assignments, and none uses GPIO 6–11 or an input-only pin for an output.

### Phase 2 — UART loopback

1. Disconnect the USB cable before wiring.
2. Connect GPIO 17 (TX) directly to GPIO 16 (RX).
3. Reconnect USB.
4. Open `SourceCode/uart_loopback/uart_loopback.ino` in Arduino IDE.
5. Select the ESP32 board profile and correct COM port.
6. Upload the sketch.
7. Open Serial Monitor and set it to **115200 baud**.
8. With the jumper connected, observe the received `PING` data.
9. Capture the output.
10. Close the Serial Monitor if necessary, disconnect USB, remove the TX-to-RX jumper, reconnect USB, and repeat the observation.
11. Record the actual behavior. A disconnected/floating RX pin can pick up noise, so do not assume it must remain perfectly silent.

**Screenshot reminder — `Documentation/screenshot-02-uart-wiring.png`**

Capture the physical TX-to-RX jumper. GPIO 17/TX and GPIO 16/RX labels must be visible.

**Screenshot reminder — `Documentation/screenshot-03-uart-loopback.png`**

Capture Serial Monitor output showing repeated received `PING` data with the jumper connected.

**Screenshot reminder — `Documentation/screenshot-04-uart-no-loopback.png`**

Capture the Serial Monitor after removing the jumper. Record any random or unexpected characters as observed rather than describing them as valid `PING` echoes.

**Checkpoint:** With the jumper connected, the received bytes should correspond to `PING` once per second. Without it, the transmitted data is no longer directly returned to RX.

### Phase 3 — I²C scanner

1. Disconnect USB before changing connections.
2. Connect module SDA to GPIO 21 and SCL to GPIO 22.
3. Connect module VCC to 3V3 and GND to GND, after confirming the module supports 3.3V operation.
4. Reconnect USB.
5. Open `SourceCode/i2c_scanner/i2c_scanner.ino`.
6. Upload the sketch.
7. Open Serial Monitor at **115200 baud**.
8. Record every address printed by the scanner.
9. Capture the output with the module connected.
10. Disconnect USB, remove the module's signal and power connections, reconnect USB, and reset or re-upload the sketch.
11. Record the no-module result.

Common example addresses include `0x3C` for many OLED displays and `0x76` or `0x77` for some BME280/BMP280 modules. These are examples only; use the address actually detected.

**Screenshot reminder — `Documentation/screenshot-05-i2c-wiring.png`**

Capture the module connected to GPIO 21/SDA, GPIO 22/SCL, 3V3, and GND. The labels should be readable.

**Screenshot reminder — `Documentation/screenshot-06-i2c-with-module.png`**

Capture the scanner output showing the address or addresses actually found.

**Screenshot reminder — `Documentation/screenshot-07-i2c-without-module.png`**

Capture the scanner output with the module disconnected. The expected message is `No I2C devices found`.

**Checkpoint:** The connected scan should identify the module if it is correctly wired and responsive. The disconnected scan should report no devices.

### Phase 4 — SPI loopback

1. Disconnect USB before wiring.
2. Connect GPIO 23 (MOSI) directly to GPIO 19 (MISO) with a jumper.
3. Keep GPIO 18 assigned to SCK and GPIO 25 assigned to CS.
4. Reconnect USB.
5. Open `SourceCode/spi_loopback/spi_loopback.ino`.
6. Upload the sketch.
7. Open Serial Monitor at **115200 baud**.
8. With MOSI and MISO jumpered, record the received byte.
9. Capture the output.
10. Disconnect USB, remove the MOSI-to-MISO jumper, reconnect USB, and repeat.
11. Record the actual received value. With MISO disconnected, its input can float, so the returned byte is not guaranteed to be a particular value.

**Screenshot reminder — `Documentation/screenshot-08-spi-wiring.png`**

Capture the MOSI-to-MISO jumper and identify GPIO 23/MOSI and GPIO 19/MISO. Include the SCK and CS assignments in the labeled diagram or photo.

**Screenshot reminder — `Documentation/screenshot-09-spi-loopback.png`**

Capture output showing `Sent 0xA5, received 0xA5` with the jumper connected.

**Screenshot reminder — `Documentation/screenshot-10-spi-no-loopback.png`**

Capture the received value after removing the jumper.

**Checkpoint:** With the jumper connected, the received byte should be `0xA5`. Without it, the value should no longer be relied upon to match the transmitted byte.

### Phase 5 — USB Serial baud-rate comparison

This test changes the baud rate of the **USB Serial connection (`Serial`)**, not the UART2 baud rate (`Serial2`).

1. Open the UART sketch.
2. Keep `Serial2.begin(9600, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);` unchanged.
3. Change `Serial.begin(115200);` to `Serial.begin(9600);`.
4. Upload the sketch.
5. Leave the Serial Monitor at **115200 baud** and observe the output.
6. Record what appears and capture it.
7. Change the Serial Monitor to **9600 baud** without changing the uploaded sketch.
8. Observe and record the readable output.
9. Restore `Serial.begin(115200);`, upload again, and restore the Serial Monitor to 115200 baud.

**Screenshot reminder — `Documentation/screenshot-11-baud-mismatch.png`**

Capture the monitor set to 115200 while the sketch's USB Serial baud is 9600. The monitor baud setting should be visible.

**Screenshot reminder — `Documentation/screenshot-12-baud-match.png`**

Capture readable output with both the sketch and Serial Monitor set to 9600.

**Checkpoint:** A baud mismatch typically produces unreadable or corrupted characters. Matching both sides at 9600 should make the text readable.

## 8. Results and Discussion

Complete the Expected versus Observed table in `ACTIVITY-ANSWERS.md` only after performing each test. Expected behavior is described there; observed behavior must come from your own Serial Monitor output.

The intended success checks are:

- UART: `PING` is received through the loopback jumper.
- I²C: the scanner reports the module's responding address.
- SPI: the loopback returns `0xA5`.
- USB Serial: readable text appears when the sketch and monitor baud rates match.

Do not claim that the objectives were achieved until the tests have been performed and the evidence has been reviewed.

## 9. Conclusion

This activity demonstrates how UART, I²C, and SPI use different signaling approaches for wired communication. UART loopback verifies serial transmission and reception, the I²C scanner identifies responding devices by address, and SPI loopback checks full-duplex data transfer using MOSI and MISO. The baud-rate comparison also demonstrates the need for matching serial settings between a sender and receiver.

After completing the experiments, add a brief personal reflection describing which tests worked, any wiring or configuration issues encountered, and what the observed results taught you.

## 10. References

- Espressif Systems, [ESP32-WROOM-32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf).
- Espressif Systems, [Arduino ESP32 Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/).
- Arduino, [Wire Library](https://docs.arduino.cc/language-reference/en/functions/communication/wire/).
- Arduino, [SPI Library](https://docs.arduino.cc/language-reference/en/functions/communication/SPI/).
- Arduino, [Serial Communication](https://docs.arduino.cc/language-reference/en/functions/communication/serial/).

## Activity Answers

See [`ACTIVITY-ANSWERS.md`](ACTIVITY-ANSWERS.md) for the completed pin table, experimental results table, and answers to the laboratory questions.
