#include <Arduino.h>
#include "sys_led.h"


void setup()
{
    SysLed::begin();
    SysLed::pattern(50, 950);
}


void loop()
{
    SysLed::loop();
}
