#pragma once
//
//    FILE: TCA9555.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: Arduino library for I2C TCA9555 16 channel port expander
//    DATE: 2021-06-09
//     URL: https://github.com/RobTillaart/TCA9555


#include "Arduino.h"
#include "Wire.h"


#define TCA9555_LIB_VERSION    (F("0.1.0"))

#define TCA9555_OK              0x00
#define TCA9555_PIN_ERROR       0x81
#define TCA9555_I2C_ERROR       0x82
#define TCA9555_VALUE_ERROR     0x83
#define TCA9555_PORT_ERROR      0x84


#define TCA9555_INVALID_READ    -100


class TCA9555
{
public:
  TCA9555(uint8_t addr, TwoWire *wire = &Wire);


#if defined(ESP8266) || defined(ESP32)
  bool    begin(const uint8_t dataPin, const uint8_t clockPin);
#endif
  bool    begin();
  bool    isConnected();


  //  single pin interface
  //  pin    = 0..15
  //  mode  = INPUT, OUTPUT
  //  value = LOW, HIGH
  bool    pinMode(uint8_t pin, uint8_t mode);
  bool    digitalWrite(uint8_t pin, uint8_t value);
  uint8_t digitalRead(uint8_t pin);
  bool    setPolarity(uint8_t pin, uint8_t value);


  //  8 pins interface
  //  port  = 0..1
  //  mask  = bitpattern
  bool    pinMode8(uint8_t port, uint8_t mask);
  bool    write8(uint8_t port, uint8_t mask);
  int     read8(uint8_t port);
  bool    setPolarity8(uint8_t port, uint8_t mask);

  int     lastError();
  
private:
  bool    writeRegister(uint8_t reg, uint8_t value);
  uint8_t readRegister(uint8_t reg);

  uint8_t   _addr;
  TwoWire*  _wire;
  uint8_t   _error;
};

// -- END OF FILE --
