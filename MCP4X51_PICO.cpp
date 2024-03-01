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
    bool taper_error_check = setTaper(taper);
    if (!taper_error_check) return false;
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
    uint16_t adjustedValue = taperPosition(thousandths);
    return writeValue(scale(adjustedValue, 0, 1000, 0, 257));
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
    int16_t value = readValue();
    if (value < 0) return value;
    return taperPosition(value, false);
}

uint32_t DigiPot_MCP4x51::scale(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t DigiPot_MCP4x51::taperPosition(uint16_t inputValue, bool write)
{
    //error check
    if (inputValue > 1000) inputValue = 1000;

    uint8_t index;
    uint16_t adjustedValue, adjustedUpperBound;

    if (write) {    
        index = (inputValue < 1000) ? inputValue / 250 : 3;
        adjustedUpperBound = (index == 3) ? 1000 : ((index + 1) * 250) - 1; 
        adjustedValue = scale(inputValue, index * 250, adjustedUpperBound, _taper_lower[index], _taper_upper[index]);
    } else {
        for (uint8_t j = 0; j < 4; j++) {
            if ((inputValue >= _taper_lower[j]) && (inputValue <= _taper_upper[j])) index = j;
        }
        adjustedUpperBound = (index == 3) ? 1000 : ((index + 1) * 250) - 1; 
        adjustedValue = scale(inputValue, _taper_lower[index], _taper_upper[index], index * 250, adjustedUpperBound);
    }
    return adjustedValue;
}

bool DigiPot_MCP4x51::setTaper(Taper taper)
{

    std::array <uint16_t, 4> lower, upper;

    switch (taper)
    {
        case TAPER_A:
            lower = { 0, 50, 150, 400 };
            upper = { 49, 149, 399, 1000};
            break;
        
        case TAPER_B:
            lower = { 0, 250, 500, 750 };
            upper = { 249, 499, 749, 1000};
            break;
        
        case TAPER_C:
            lower = { 0, 600, 850, 950 };
            upper = { 599, 849, 949, 1000};
            break;
        
        case TAPER_W:
            lower = { 0, 50, 500, 950 };
            upper = { 49, 499, 949, 1000};
            break;
        
        case TAPER_M:
            lower = { 0, 500, 1000, 1000 };
            upper = { 499, 1000, 1000, 1000};
            break;
        
        case TAPER_N:
            lower = { 1000, 1000, 500, 0 };
            upper = { 1000, 1000, 1000, 499};
            break;
        
        case TAPER_CUSTOM:
        default:
            return false;
            break;
    }
    _taper = taper;
    for (uint8_t i = 0; i < 4; i++) {
        _taper_lower[i] = lower[i];
        _taper_upper[i] = upper[i];
    }
    return true;
}

bool DigiPot_MCP4x51::setTaper(uint16_t lower_bounds[4], uint16_t upper_bounds[4])
{
    _taper = TAPER_CUSTOM;
    for (uint8_t i = 0; i < 4; i++) {
        _taper_lower[i] = lower_bounds[i];
        _taper_upper[i] = upper_bounds[i];
    }
    return true;
}

Taper DigiPot_MCP4x51::getTaper()
{
    return _taper;
}
