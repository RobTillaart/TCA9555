//
//    FILE: TCA9555_getType.ino
//  AUTHOR: Rob Tillaart
// PUPROSE: test TCA9555 library - TCA9535 derived class
//     URL: https://github.com/RobTillaart/TCA9555


#include "Wire.h"
#include "TCA9555.h"


TCA9555 TCA0(0x20);
TCA9535 TCA1(0x21);


void setup()
{
  Serial.begin(115200);
  Serial.print("TCA9555_LIB_VERSION: ");
  Serial.println(TCA9555_LIB_VERSION);

  Serial.println(TCA0.getType());
  Serial.println(TCA1.getType());
}


void loop()
{
}


// -- END OF FILE --
