
[![Arduino CI](https://github.com/RobTillaart/TCA9555/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/TCA9555/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/TCA9555/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/TCA9555/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/TCA9555/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/TCA9555/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/TCA9555.svg?maxAge=3600)](https://github.com/RobTillaart/TCA9555/releases)


# TCA9555

Arduino library for TCA9555 16 channel I2C port expander.


## Description

This library gives easy control over the 16 pins of a TCA9555 chip.

The TCA9555 supports up to 400 kHz I2C.


#### TCA9535

from datasheet:

_The TCA9535 is identical to the TCA9555, except that the TCA9535 does not include the internal I/O
pull-up resistor, which requires pull-ups and pull-downs on unused I/O pins when configured as an
input and not driven. This reduces power consumption when the I/O is held low._

There is a TCA9535 class which is a (convenience) wrapper around the TCA9555 class. 
This allows one to create TCA9535 objects. 


## Hardware

#### I2C addresses

Allowed addresses are 0x20..0x27. to be set with pin A0, A1, A2.


## Interface

Check the datasheet for details

```cpp
#include "TCA9555.h"
```

#### Constructor

- **TCA9555(uint8_t address, TwoWire \*wire = &Wire)** constructor, with default Wire interface. 
Can be overruled with Wire0..WireN.
- **TCA9535(uint8_t address, TwoWire \*wire = &Wire)** idem.
- **uint8_t getType()** returns 35 or 55 depending on type.


- **bool begin()** for UNO, returns true if successful.
- **bool begin(uint8_t sda, uint8_t scl)** for ESP32, returns true if successful.
- **bool isConnected()** returns true if connected, false otherwise.
- **uint8_t getAddress()** returns set address, (debugging).


#### 1 pin interface

- **bool pinMode(uint8_t pin, uint8_t mode)** idem.
- **bool digitalWrite(uint8_t pin, uint8_t value)** pin = 0..15, value = LOW(0) HIGH (!0), returns true if successful.
- **uint8_t digitalRead(uint8_t pin)** pin = 0..15, returns the value of the pin HIGH or LOW.
- **bool setPolarity(uint8_t pin, uint8_t value)** inverts polarity of an INPUT pin.
- **uint8_t getPolarity(uint8_t pin)** returns 1 if a pin is inverted.


#### 8 pin interface

port = 0..1  
mask = 0..255

- **bool pinMode8(uint8_t port, uint8_t mask)** set the mode of eight pins in one call.
- **bool write8(uint8_t port, uint8_t mask)** returns true if successful. 
Especially useful if one needs to trigger multiple pins at the exact same time.
- **uint8_t read8(uint8_t port)** returns a bit pattern for pins 0..7 or pins 8..15.
- **bool setPolarity8(uint8_t port, uint8_t mask)** inverts polarity of the 8 INPUT pins in one action.
- **uint8_t getPolarity(uint8_t port)** returns a mask with a 1 for every INPUT pin that is inverted.


#### 16 pin interface

Be aware that the 16 pins interface does two calls to the 8 pins interface. 
So it is impossible to switch pins from the 2 groups of 8 at exactly the same time 
without additional hardware.

- **bool pinMode16(uint16_t mask)** set the mode of sixteen pins in one call. 
- **bool write16(uint16_t mask)**  mask = 0x0000 .. 0xFFFF, returns true if successful.
- **uint16_t read16()** Returns a bit pattern for pins 0..15.
- **bool setPolarity16(uint16_t mask)** inverts polarity of the 8 INPUT pins in one action. 
Returns true upon success.
- **uint16_t getPolarity()** returns a mask of 16 bits with a 1 for every INPUT pin that is inverted.


#### Error codes

- **int lastError()** Above functions set an error flag that can be read with this function. 
Reading it will reset the flag to **TCA9555_OK**.


|  Description           |  Value  |
|:-----------------------|:-------:|
|  TCA9555_OK            |  0x00   |
|  TCA9555_PIN_ERROR     |  0x81   |
|  TCA9555_I2C_ERROR     |  0x82   |
|  TCA9555_VALUE_ERROR   |  0x83   |
|  TCA9555_PORT_ERROR    |  0x84   |
|  TCA9555_INVALID_READ  |  -100   |


## Operation

See examples


## Future


#### Must

- buy TCA9555 / TCA9535
- test all functionality
  - library is written without hardware


#### Should

- investigate map INPUT_PULLUP on INPUT (pinMode ?)
- investigate internal pull up etc.
- investigate TCA9535 differences
  - pull up resistors
  - elaborate derived class


#### Could

- rethink class hierarchy
  - TCA9535 has less functions so should be base class?
- valid address range?


#### Wont (unless)
- add TCA9535 error codes
  - better reuse them?
