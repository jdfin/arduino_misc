#include <Arduino.h>
#include "sys_led.h"


void setup()
{
    SysLed::begin();
}


void loop()
{
    const unsigned long on_ms = 250;
    const unsigned long off_ms = 750;

    SysLed::on();

    delay(on_ms);

    SysLed::off();

    delay(off_ms);
}
