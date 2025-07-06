#include <Arduino.h>
#include "sys_led.h"

unsigned long SysLed::_on_ms;
unsigned long SysLed::_off_ms;
unsigned long SysLed::_on_next_ms;
unsigned long SysLed::_off_next_ms;
