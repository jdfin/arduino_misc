#pragma once

#include <Arduino.h>


// Tested with:
// -DARDUINO_RASPBERRY_PI_PICO
// -DARDUINO_PIMORONI_TINY2040


class SysLed {

    public:

        static void begin()
        {
#ifdef ARDUINO_PIMORONI_TINY2040
            // RGB LED
            pinMode(red_gpio, OUTPUT);
            pinMode(green_gpio, OUTPUT);
            pinMode(blue_gpio, OUTPUT);
            digitalWrite(red_gpio, 1 - on_val);
            digitalWrite(green_gpio, 1 - on_val);
            digitalWrite(blue_gpio, 1 - on_val);
#else
            pinMode(led_gpio, OUTPUT);
#endif
            off();
        }

        // 1=on, 0=off
        static void set(int on)
        {
            digitalWrite(led_gpio, on ? on_val : (1 - on_val));

            _on_ms = 0;
            _off_ms = 0;
        }

        static void on()
        {
            set(1);
        }

        static void off()
        {
            set(0);
        }

        // on for on_ms, off for off_ms, repeat
        static void pattern(uint32_t on_ms, uint32_t off_ms)
        {
            _on_ms = on_ms;
            _off_ms = off_ms;

            if (_on_ms > 0) {
                _on_next_ms = millis();
                _off_next_ms = ULONG_MAX;
            } else if (_off_ms > 0) {
                _on_next_ms = ULONG_MAX;
                _off_next_ms = millis();
            } // else pattern disabled by _on_ms = _off_ms = 0

            loop();
        }

        // This only has to be called if pattern() needs to work.
        // It will also behave unexpectedly when millis() overflows
        // (probably 49 days since we treat it as unsigned here),
        // but shouldn't crash or hang.
        static void loop()
        {
            if (_on_ms == 0 && _off_ms == 0)
                return;

            unsigned long now_ms = millis();
            if (_on_next_ms <= now_ms) {
                digitalWrite(led_gpio, on_val); // on
                _on_next_ms = ULONG_MAX;
                // if s2 should be on for any duration,
                // schedule it to come on after s1's duration
                if (_off_ms > 0) {
                    _off_next_ms = now_ms + _on_ms;
                }
            } else if (_off_next_ms <= now_ms) {
                digitalWrite(led_gpio, 1 - on_val); // off
                _off_next_ms = ULONG_MAX;
                if (_on_ms > 0) {
                    _on_next_ms = now_ms + _off_ms;
                }
            }
        }

    private:

        static unsigned long _on_ms;
        static unsigned long _off_ms;
        static unsigned long _on_next_ms;
        static unsigned long _off_next_ms;

#ifdef ARDUINO_PIMORONI_TINY2040
        static const int red_gpio = 18;
        static const int green_gpio = 19;
        static const int blue_gpio = 20;
        static const int led_gpio = green_gpio;

        static const int on_val = 0;
        static const int off_val = 1;
#else
        static const int led_gpio = LED_BUILTIN;
        static const int on_val = 1;
        static const int off_val = 0;
#endif

}; // class SysLed
