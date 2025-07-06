#include <Arduino.h>
#include "sys_led.h"


void xassert_func(const char *file, int line, const char *expr)
{
    SysLed::begin();            // ok if this has already been called

    SysLed::pattern(250, 250);  // blinking at 2 Hz is supposed to say
                                // "plug in serial to see what happened"

    Serial.begin(115200);
    while (!Serial)
        SysLed::loop();

    Serial.printf("assertion \"%s\" failed: file \"%s\", line %d\n",
                  expr, file, line);

    while (true)
        SysLed::loop();
}
