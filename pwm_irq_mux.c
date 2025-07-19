#include <Arduino.h>
#include "hardware/irq.h"
#include "hardware/pwm.h"

#include "pwm_irq_mux.h"


// handlers for 8 slices
static volatile struct {
    void (*func)(void*);
    void *arg;
} pwm_irq_mux_handlers[NUM_PWM_SLICES];


void pwm_irq_handler()
{
    uint32_t ints = pwm_get_irq_status_mask();

    // datasheet doesn't say what the upper bits are; clear them
    ints &= ((1 << NUM_PWM_SLICES) - 1); // 8 -> 0xff

    while (ints != 0) {
        uint slice = ffs(ints) - 1;
        pwm_irq_mux_handlers[slice].func(pwm_irq_mux_handlers[slice].arg);
        pwm_clear_irq(slice);
        ints &= ~(1 << slice); // clear bit in ints
    }
}


// install a handler
void pwm_irq_mux_connect(uint slice, void (*func)(void*), void *arg)
{
    static bool init = false;

    if (!init) {
        for (uint slice = 0; slice < NUM_PWM_SLICES; slice++) {
            pwm_irq_mux_handlers[slice].func = NULL;
            pwm_irq_mux_handlers[slice].arg = NULL;
            pwm_set_irq_enabled(slice, false);
            pwm_clear_irq(slice);
        }
        irq_set_exclusive_handler(PWM_IRQ_WRAP, pwm_irq_handler);
        irq_set_enabled(PWM_IRQ_WRAP, true);
        init = true;
    }

    pwm_irq_mux_handlers[slice].func = func;
    pwm_irq_mux_handlers[slice].arg = arg;
}
