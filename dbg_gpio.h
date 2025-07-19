#pragma once

#include <Arduino.h>
#include <initializer_list>
#include "hardware/gpio.h"


class DbgGpio {

    public:

        inline DbgGpio(int gpio) : _gpio(gpio)
        {
            gpio_put(_gpio, 1);
        }

        inline ~DbgGpio()
        {
            gpio_put(_gpio, 0);
        }

        static void init(int gpio)
        {
            gpio_put(gpio, 0);
            gpio_init(gpio);
            gpio_set_dir(gpio, GPIO_OUT);
        }

        static void init(std::initializer_list<int> gpios)
        {
            for (int gpio : gpios)
                init(gpio);
        }

    private:

        int _gpio;

}; // class DbgGpio
