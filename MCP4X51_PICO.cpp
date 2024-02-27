/**************************************************
 * PICO_MCP4X51 Library v1.1 (2024-02-25)
 * Written by Abe Friedman 
 * github.com/rabbiabe
 **************************************************/

#include "MCP4X51_PICO.h"

DigiPot_MCP4x51::DigiPot_MCP4x51()
{

}

bool DigiPot_MCP4x51::init(uint8_t pin_cs, uint8_t pot, Taper taper, uint16_t wiper)
{
    _select = pin_cs;
    _address = pot << 4;
    setTaper(taper);

    spi_init(SPI_CHANNEL, SPI_10_MHZ);
    spi_set_format(spi0, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    return writeValue(wiper);
}

bool DigiPot_MCP4x51::increment()
{
    uint8_t spi_data = _address | _cmd_increment;
    uint8_t spi_recv;
    gpio_put(_select, false);
    spi_write_read_blocking(SPI_CHANNEL, &spi_data, &spi_recv, 1);
    gpio_put(_select, true);
    return spi_recv | _mask_err;

}

bool DigiPot_MCP4x51::decrement()
{
    uint8_t spi_data = _address | _cmd_decrement;
    uint8_t spi_recv;
    gpio_put(_select, false);
    spi_write_read_blocking(SPI_CHANNEL, &spi_data, &spi_recv, 1);
    gpio_put(_select, true);
    return spi_recv | _mask_err;

}

bool DigiPot_MCP4x51::writeValue(uint16_t value)
{
    uint16_t spi_data = ((_address | _cmd_write) << 8) | value;
    uint16_t spi_recv;
    gpio_put(_select, false);
    spi_write16_read16_blocking(SPI_CHANNEL, &spi_data, &spi_recv, 1);
    gpio_put(_select, true);
    return (spi_recv >> 8) | _mask_err;

}

bool DigiPot_MCP4x51::writePosition(uint16_t thousandths) 
{
    uint16_t taperedValue = getTaperedValue(thousandths);
    return writeValue(scale(taperedValue, 0, 1000, 0, 257));
}


int16_t DigiPot_MCP4x51::readValue()
{

    uint16_t spi_data = ((_address | _cmd_read) << 8);
    uint16_t spi_recv;
    gpio_put(_select, false);
    spi_write16_read16_blocking(SPI_CHANNEL, &spi_data, &spi_recv, 1);
    gpio_put(_select, true);
    if ((spi_recv >> 8) | _mask_err) {
        return (int16_t)(spi_recv & _mask_data);
    } else {
        return -1;
    }


}

int16_t DigiPot_MCP4x51::readPosition()
{
    return(scale(readValue(), 0, 257, 0, 1000));
}


uint32_t DigiPot_MCP4x51::scale(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t DigiPot_MCP4x51::getTaperedValue(uint16_t inputValue)
{
    
    //error check
    if (inputValue > 1000) inputValue = 1000;

    uint16_t adjustedValue;

    switch (_taper)
    {
        case TAPER_A:
            if (inputValue < 250) { 
                adjustedValue = scale(inputValue, 0, 249, 0, 49);
            } else if (inputValue >= 250 && inputValue < 500) {
                adjustedValue = scale(inputValue, 250, 499, 50, 149);
            } else if (inputValue >= 500 && inputValue < 750) {
                adjustedValue = scale(inputValue, 500, 749, 150, 399);
            } else {
                adjustedValue = scale(inputValue, 750, 1000, 400, 1000);
            }
            break;
        
        case TAPER_B:
        default:
            adjustedValue = inputValue;
            break;

        case TAPER_C:
            if (inputValue < 250) { 
                adjustedValue = scale(inputValue, 0, 249, 0, 599);
            } else if (inputValue >= 250 && inputValue < 500) {
                adjustedValue = scale(inputValue, 250, 499, 600, 849);
            } else if (inputValue >= 500 && inputValue < 750) {
                adjustedValue = scale(inputValue, 500, 749, 850, 949);
            } else {
                adjustedValue = scale(inputValue, 750, 1000, 950, 1000);
            }
            break;

        case TAPER_W:
            if (inputValue < 250) { 
                adjustedValue = scale(inputValue, 0, 249, 0, 49);
            } else if (inputValue >= 250 && inputValue < 750) {
                adjustedValue = scale(inputValue, 250, 749, 50, 949);
            } else {
                adjustedValue = scale(inputValue, 750, 1000, 950, 1000);
            }
            break;
        }

  return adjustedValue;
}

void DigiPot_MCP4x51::setTaper(Taper taper)
{
    _taper = taper;
}

Taper DigiPot_MCP4x51::getTaper()
{
    return _taper;
}