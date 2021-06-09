//
//    FILE: TCA9555.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for I2C TCA9555 16 channel port expander
//    DATE: 2021-06-09
//     URL: https://github.com/RobTillaart/TCA9555
//
//  HISTORY:
//  0.1.0   2021-06-09  initial version


#include "TCA9555.h"


// REGISTERS
#define TCA9555_INPUT_PORT_REGISTER_0     0x00
#define TCA9555_INPUT_PORT_REGISTER_1     0x01
#define TCA9555_OUTPUT_PORT_REGISTER_0    0x02
#define TCA9555_OUTPUT_PORT_REGISTER_1    0x03
#define TCA9555_POLARITY_REGISTER_0       0x04
#define TCA9555_POLARITY_REGISTER_1       0x05
#define TCA9555_CONFIGURATION_PORT_0      0x06
#define TCA9555_CONFIGURATION_PORT_1      0x07


TCA9555::TCA9555(uint8_t addr, TwoWire *wire)
{
  _addr  = addr;
  _wire  = wire;
  _error = TCA9555_OK;
}


#if defined(ESP8266) || defined(ESP32)
bool TCA9555::begin(const uint8_t dataPin, const uint8_t clockPin)
{
  _wire = &Wire;
  _wire->begin(dataPin, clockPin);
  if (! isConnected()) return false;
  return true;
}
#endif


bool TCA9555::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  return true;
}


bool TCA9555::isConnected()
{
  _wire->beginTransmission(_addr);
  return (_wire->endTransmission() == 0);
}


bool TCA9555::pinMode(uint8_t pin, uint8_t mode)
{
  if (pin > 15)
  {
    _error = TCA9555_PIN_ERROR;
    return false;
  }
  uint8_t CONFREG = TCA9555_CONFIGURATION_PORT_0;
  if (pin > 7)
  {
    CONFREG = TCA9555_CONFIGURATION_PORT_1;
    pin -= 8;
  }
  uint8_t val = readRegister(CONFREG);
  uint8_t mask = 1 << pin;
  if (mode == INPUT)  val |= mask;
  if (mode == OUTPUT) val &= ~mask;
  writeRegister(CONFREG, val);
  _error = TCA9555_OK;
  return true;
}


bool TCA9555::digitalWrite(uint8_t pin, uint8_t value)   // pin = 0..15
{
  if (pin > 15)
  {
    _error = TCA9555_PIN_ERROR;
    return false;
  }
  uint8_t OPR = TCA9555_OUTPUT_PORT_REGISTER_0;
  if (pin > 7)
  {
    OPR = TCA9555_OUTPUT_PORT_REGISTER_1;
    pin -= 8;
  }
  uint8_t val = readRegister(OPR);
  uint8_t mask = 1 << pin;
  if (value) val |= mask;
  else val &= ~mask;
  writeRegister(OPR, val);
  _error = TCA9555_OK;
  return true;
}


uint8_t TCA9555::digitalRead(uint8_t pin)
{
  if (pin > 15)
  {
    _error = TCA9555_PIN_ERROR;
    return TCA9555_INVALID_READ;
  }
  uint8_t IPR = TCA9555_INPUT_PORT_REGISTER_0;
  if (pin > 7)
  {
    IPR = TCA9555_INPUT_PORT_REGISTER_1;
    pin -= 8;
  }
  uint8_t val = readRegister(IPR);
  uint8_t mask = 1 << pin;
  _error = TCA9555_OK;
  if (val & mask) return HIGH;
  return LOW;
}


bool TCA9555::setPolarity(uint8_t pin, uint8_t value)   // pin = 0..15
{
  if (pin > 15)
  {
    _error = TCA9555_PIN_ERROR;
    return false;
  }
  uint8_t POLREG = TCA9555_POLARITY_REGISTER_0;
  if (pin > 7)
  {
    POLREG = TCA9555_POLARITY_REGISTER_1;
    pin -= 8;
  }
  uint8_t val = readRegister(POLREG);
  uint8_t mask = 1 << pin;
  if (value == HIGH) val |= mask;
  if (value == LOW)  val &= ~mask;
  writeRegister(POLREG, val);
  _error = TCA9555_OK;
  return true;
}


bool TCA9555::pinMode8(uint8_t pin, uint8_t mask)
{
  if (pin > 15)
  {
    _error = TCA9555_PIN_ERROR;
    return false;
  }
  uint8_t CONFREG = TCA9555_CONFIGURATION_PORT_0;
  if (pin > 7)
  {
    CONFREG = TCA9555_CONFIGURATION_PORT_1;
    pin -= 8;
  }
  uint8_t val = readRegister(CONFREG);
  uint8_t mask = 1 << pin;
  if (value) val |= mask;
  else val &= ~mask;
  writeRegister(CONFREG, val);
  _error = TCA9555_OK;
  return true;
}


bool TCA9555::write8(uint8_t port, uint8_t mask)   // port = 0..1
{
  if (port > 1)
  {
    _error = TCA9555_PORT_ERROR;
    return false;
  }
  if (port == 0) writeRegister(TCA9555_OUTPUT_PORT_REGISTER_0, mask);
  if (port == 1) writeRegister(TCA9555_OUTPUT_PORT_REGISTER_1, mask);
  _error = TCA9555_OK;
  return true;
}


int TCA9555::read8(uint8_t port)
{
  if (port > 1)
  {
    _error = TCA9555_PORT_ERROR;
    return TCA9555_INVALID_READ;
  }
  _error = TCA9555_OK;
  if (port == 0) return readRegister(TCA9555_OUTPUT_PORT_REGISTER_0);
  if (port == 1) return readRegister(TCA9555_OUTPUT_PORT_REGISTER_1);
  return; // keeps compiler happy
}


bool TCA9555::setPolarity8(uint8_t port, uint8_t mask)   // pin = 0..15
{
  if (port > 1)
  {
    _error = TCA9555_PORT_ERROR;
    return false;
  }
  uint8_t POLREG = TCA9555_POLARITY_REGISTER_0;
  if (pin > 7)
  {
    POLREG = TCA9555_POLARITY_REGISTER_1;
    pin -= 8;
  }
  uint8_t value = readRegister(POLREG);
  uint8_t mask = 1 << pin;
  if (value == LOW)  value &= ~mask;
  else value |= mask;
  writeRegister(POLREG, value);
  _error = TCA9555_OK;
  return true;
}


int TCA9555::lastError()
{
  int e = _error;
  _error = TCA9555_OK;  // reset error after read.
  return e;
}


////////////////////////////////////////////////////
//
// PRIVATE
// 

bool TCA9555::writeRegister(uint8_t reg, uint8_t value)
{
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  _wire->write(value);
  if (_wire->endTransmission() != 0)
  {
    _error = TCA9555_I2C_ERROR;
    return false;
  }
  _error = TCA9555_OK;
  return true;
}


uint8_t TCA9555::readRegister(uint8_t reg)
{
  _wire->beginTransmission(_addr);
  _wire->write(reg);
  int rv = _wire->endTransmission();
  if (rv != 0)
  {
    _error = TCA9555_I2C_ERROR;
    return rv;
  }
  else
  {
    _error = TCA9555_OK;
  }
  _wire->requestFrom(_addr, (uint8_t)1);
  return _wire->read();
}


// -- END OF FILE --
