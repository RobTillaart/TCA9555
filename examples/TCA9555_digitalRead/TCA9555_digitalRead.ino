//
//    FILE: TCA9555_digitalRead.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test TCA9555 library
//     URL: https://github.com/RobTillaart/TCA9555


#include "TCA9555.h"


TCA9555 TCA(0x27);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9555_LIB_VERSION: ");
  Serial.println(TCA9555_LIB_VERSION);
  Serial.println();

  Wire.begin();
  TCA.begin();

  Serial.println("TEST read1(pin)");
  for (int pin = 0; pin < 16; pin++)
  {
    int val = TCA.read1(pin);
    Serial.print(val);
    Serial.print('\t');
  }
  Serial.println(); 
}


void loop()
{
}


//  -- END OF FILE --

