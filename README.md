
[![Arduino CI](https://github.com/RobTillaart/TCA9555/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TCA9555/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TCA9555.svg?maxAge=3600)](https://github.com/RobTillaart/TCA9555/releases)

# TCA9555

Arduino library for TCA9555 16 channel I2C port expander


## Description

This library gives easy control over the 16 pins of a TCA9555 chip.


## Interface

### Constructor

- **TCA9555(uint8_t address, TwoWire \*wire = &Wire)** constructor, with default Wire interface. Can be overruled with Wire0..WireN
- **bool begin()** for UNO, returns true if successful
- **bool begin(uint8_t sda, uint8_t scl)** for ESP32, returns true if successful
- **bool isConnected()** returns true if connected, false otherwise


### single pin interface

- **bool digitalWrite(uint8_t pin, uint8_t value)** pin = 0..15, value = LOW(0) HIGH (!0), returns true if successful.
- **uint8_t digitalRead(uint8_t pin)** pin = 0..15


### 8 pins interface

- **bool write8(uint8_t port, uint8_t value)** port = 0, 1  value = 0..255, returns true if successful.
- **uint8_t read8(uint8_t port)** port = 0, 1


### Error codes

- **int lastError()** Above functions set an error flag that can be read withthis function. Reading it will reset the flag to **TCA9555_OK**.

| DESCRIPTION          | VALUE |
|:---------------------|:-----:|
| TCA9555_OK           |  0x00 |
| TCA9555_PIN_ERROR    |  0x81 |
| TCA9555_I2C_ERROR    |  0x82 |
| TCA9555_VALUE_ERROR  |  0x83 |
| TCA9555_PORT_ERROR   |  0x84 |


## Future

- set pull up
- polarity inversion register
- ...


## Operation

See examples

