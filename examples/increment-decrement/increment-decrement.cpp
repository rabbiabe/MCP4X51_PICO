#include "increment-decrement.h"
#include "../../MCP4X51_PICO.h"

/**************************************************
 * This example demonstrates the increment() and 
 * decrement() functions using two push buttons. 
 * Holding a button will double the step speed 
 * every 5 seconds.
 **************************************************/

DigiPot_MCP4x51 potentiometer;

volatile uint32_t stepTime, pressTime;
volatile bool goingUp;

int main()
{
    if (!stdio_init_all()) return -1;

    uint32_t initMask = (1 << pinBtnDown) || (1 << pinBtnUp);
    
    gpio_init_mask(initMask);
    gpio_set_dir_out_masked(initMask);
    
    gpio_set_irq_enabled_with_callback(pinBtnDown, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, buttonPress);
    gpio_set_irq_enabled(pinBtnUp, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);

    gpio_set_function(pinCOPI, GPIO_FUNC_SPI);
    gpio_set_function(pinCIPO, GPIO_FUNC_SPI);
    gpio_set_function(pinSCK, GPIO_FUNC_SPI);
    gpio_set_function(pinCS, GPIO_FUNC_SPI);

    potentiometer.init(pinCS, 0, TAPER_B);

    while (true)
    {
        if (pressTime > 0) {
            if (time_us_32() % stepTime == 0) moveWiper();
            if (time_us_32() - pressTime > 5000000) {
                pressTime = time_us_32();
                stepTime >> 1;
            }
        }
    }    

    return 0;
}

void buttonPress(uint gpio, uint32_t event_mask)
{
    switch (event_mask)
    {
        case GPIO_IRQ_EDGE_FALL:
            pressTime = time_us_32();
            goingUp = (gpio == pinBtnUp) ? true : false;
            moveWiper();
            break;
        
        case GPIO_IRQ_EDGE_RISE:
            pressTime = 0;
            stepTime = 1000000;
            break;
        
        default:
            break;
    }
}

void moveWiper()
{
    if (goingUp) {
        potentiometer.increment();
    } else {
        potentiometer.decrement();
    }
}