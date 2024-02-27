/**************************************************
 * PICO_MCP4X51 Library v1.1 (2024-02-25)
 * Written by Abe Friedman 
 * github.com/rabbiabe
 **************************************************/


#pragma once



#include <cstdint>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#define SPI_10_MHZ 10000000
#define SPI_CHANNEL spi0

enum Taper {
    TAPER_A,
    TAPER_B,
    TAPER_C,
    TAPER_W,
};

class DigiPot_MCP4x51 {
    public:

        DigiPot_MCP4x51();
        bool init(uint8_t pin_cs, uint8_t pot, Taper taper = TAPER_B, uint16_t wiper = 128);
        bool increment();
        bool decrement();
        bool writeValue(uint16_t value);
        bool writePosition(uint16_t thousandths);
        int16_t readValue();
        int16_t readPosition();
        void setTaper(Taper taper);
        Taper getTaper();

        


    private:

        uint32_t scale(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);
        uint16_t getTaperedValue(uint16_t inputValue);

        uint8_t _select, _address;
        Taper _taper;

        const uint8_t  _cmd_write     = 0b0000'0000;
        const uint8_t  _cmd_read      = 0b0000'1100;
        const uint8_t  _cmd_increment = 0b0000'0100;
        const uint8_t  _cmd_decrement = 0b0000'1000;
        const uint8_t  _mask_err      = 0b0000'0010;
        const uint16_t _mask_data     = 0b0000'0001'1111'1111;


};