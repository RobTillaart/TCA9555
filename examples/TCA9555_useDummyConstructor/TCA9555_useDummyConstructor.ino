//
//  FILE: TCA9555_blank_constructor.ino
//  AUTHOR: Gerry Gralton
//  PUPROSE: test TCA9555 library
//  URL: https://github.com/RobTillaart/TCA9555


#include "Wire.h"
#include "TCA9555.h"


TCA9555 TCA(0x27);

class Object{
    TCA9555 Object_TCA;

    public:
    Object ( TCA9555 TCA_param ){
        this->Object_TCA = TCA_param;
    }
};

void setup() {
    Object obj = Object ( TCA );
}

void loop() {

}
