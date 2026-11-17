# Laboratory Activity Answers

**Subject:** Not specified in the supplied activity  
**Laboratory Activity:** Verification of the Three Wired Interfaces on an ESP32 (UART, I²C, and SPI)

> **Important:** The Expected column below is a prediction based on the activity instructions. Complete the Observed column only after running the tests on your own ESP32. Do not present predictions as experimental observations.

## 1. Pin Assignment Table

Suggested GPIO assignments for a classic ESP32-WROOM-32 DevKit. Confirm them against the exact board pinout before wiring.

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

All eight signals use distinct GPIOs. GPIO 6–11 are avoided because they are generally connected to flash, and GPIO 34–39 are avoided because they are input-only. This assignment is intended for a classic WROOM-32 board, not a WROVER board with PSRAM-related pin reservations.

## 2. Expected versus Observed Table

Fill in **Observed** after completing each physical test. Include concise details and, where useful, the exact output or received value.

| Test | Expected | Observed |
|---|---|---|
| UART with jumper | The ESP32 receives the transmitted `PING` bytes through the TX-to-RX jumper, approximately once per second. | **Pending actual test.** |
| UART without jumper | The transmitted `PING` is not directly looped back to RX. The RX input may float and can show noise or random characters. | **Pending actual test.** |
| I²C with module | The scanner prints `Found device at 0x..` for the module's responding address. Example addresses include `0x3C`, `0x76`, or `0x77`, depending on the module. | **Pending actual test. Record exact address(es).** |
| I²C without module | The scanner prints `No I2C devices found`, assuming no other I²C device is connected. | **Pending actual test.** |
| SPI with jumper | The received byte is `0xA5`, matching the transmitted byte, because MOSI is connected to MISO. | **Pending actual test.** |
| SPI without jumper | The received byte is no longer guaranteed to be `0xA5`. MISO may float, so the value can vary. | **Pending actual test. Record exact value.** |
| Sketch at 9600, monitor at 115200 | The USB Serial output is expected to appear corrupted or unreadable because the baud rates do not match. | **Pending actual test.** |
| Sketch at 9600, monitor at 9600 | The USB Serial output should be readable because both sides use the same baud rate. | **Pending actual test.** |

## 3. Activity Questions

### 1. Why does UART need both sides to use the same baud rate, while SPI uses a clock line?

UART is asynchronous, so the transmitter and receiver must agree on a baud rate to interpret the timing of each bit correctly. SPI is synchronous because the controller supplies a clock signal that tells the receiving device when to sample each bit.

### 2. Why can two devices with the same address not share one I²C bus?

Each I²C device must have a unique address on the bus so the controller can select the intended device. If two devices use the same address, both may respond to the same request, causing address conflicts and potentially unreliable or corrupted communication.

### 3. Why is CS set HIGH between SPI transfers?

CS (Chip Select) is active LOW for this test, so setting it HIGH deactivates the selected device between transfers. This prevents the device from treating unrelated clock and data activity as part of its transaction and allows the controller to select it again when needed.

## 4. Wiring Documentation

Create and save a labeled wiring diagram or clearly labeled physical photographs.

### UART loopback

- ESP32 GPIO 17 — TX
- Jumper: GPIO 17/TX to GPIO 16/RX
- ESP32 GPIO 16 — RX

### I²C module

| Module pin | ESP32 pin |
|---|---|
| SDA | GPIO 21 |
| SCL | GPIO 22 |
| VCC/VIN | 3V3, if supported by the module |
| GND | GND |

### SPI loopback

- ESP32 GPIO 18 — SCK
- ESP32 GPIO 23 — MOSI
- Jumper: GPIO 23/MOSI to GPIO 19/MISO
- ESP32 GPIO 19 — MISO
- ESP32 GPIO 25 — CS

**Evidence files:** Add the wiring diagram or photos to the `Documentation/` folder using the filenames listed in `README.md`.

## 5. Observations and Analysis

Complete this section after testing.

- **UART with jumper:** [Record whether `PING` was received and whether it appeared approximately once per second.]
- **UART without jumper:** [Record whether the output stopped, became random, or showed other behavior.]
- **I²C with module:** [Record the exact address or addresses detected.]
- **I²C without module:** [Record the exact scanner message.]
- **SPI with jumper:** [Record the received byte.]
- **SPI without jumper:** [Record the received byte and whether it differed from `0xA5`.]
- **Baud mismatch:** [Describe what appeared at 115200 monitor baud while USB Serial was configured to 9600.]
- **Baud match:** [Describe the output after setting the monitor to 9600.]

## 6. References

- Espressif Systems, [ESP32-WROOM-32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf).
- Espressif Systems, [Arduino ESP32 Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/).
- Arduino, [Wire Library](https://docs.arduino.cc/language-reference/en/functions/communication/wire/).
- Arduino, [SPI Library](https://docs.arduino.cc/language-reference/en/functions/communication/SPI/).
- Arduino, [Serial Communication](https://docs.arduino.cc/language-reference/en/functions/communication/serial/).
