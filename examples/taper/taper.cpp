#include "taper.h"
#include "../../MCP4X51_PICO.h"

/**************************************************
 * This example reads the analog voltage from a 
 * potentiometer divider and uses it to set the
 * digital potentiometer. While this minimal setup 
 * essentially replicates the function of a 
 * passive potentiometer, it also allows for real-
 * time changing of the potentiometer taper during 
 * the init() routine or by calling setTaper() 
 * directly. The library currently supports A, B, 
 * C, and W tapers. Support for MN and custom 
 * tapers may be added in the future.
 * 
 * In addition to the potentiomter, a push button
 * is used to cycle through the available tapers.
 **************************************************/

DigiPot_MCP4x51 potentiometer;
volatile Taper activeTaper = TAPER_A;

int main()
{
    if (!stdio_init_all()) return -1;

    gpio_init(pinTaperSelect);
    gpio_set_dir(pinTaperSelect, false);

    gpio_set_irq_enabled_with_callback(pinTaperSelect, GPIO_IRQ_EDGE_FALL, true, taperSelect);

    adc_init();
    adc_gpio_init(pinPot);
    if ((pinPot < 26) || (pinPot > 28)) return 1; // pinPot must be 26, 27, or 28 – ADC pins
    adc_select_input(pinPot - 26); 

    gpio_set_function(pinCOPI, GPIO_FUNC_SPI);
    gpio_set_function(pinCIPO, GPIO_FUNC_SPI);
    gpio_set_function(pinSCK, GPIO_FUNC_SPI);
    gpio_set_function(pinCS, GPIO_FUNC_SPI);

    potentiometer.init(pinCS, 0, activeTaper);

    while (true)
    {
        if ((time_us_32() % 50000) == 0) potentiometer.writePosition((adc_read() * 1000) / 4095);
    }    

    return 0;
}

void taperSelect(uint gpio, uint32_t event_mask)
{
    switch (activeTaper)
    {
        case TAPER_A:
            activeTaper = TAPER_B;
            break;
        
        case TAPER_B:
            activeTaper = TAPER_C;
            break;
        
        case TAPER_C:
            activeTaper = TAPER_W;
            break;
        
        case TAPER_W:
            activeTaper = TAPER_A;
            break;
        
        default:
            activeTaper = TAPER_B;
            break;
    }
    potentiometer.setTaper(activeTaper);
}