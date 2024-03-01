/**************************************************
 * PICO_MCP4X51 Library v1.1 (2024-02-25)
 * Written by Abe Friedman 
 * github.com/rabbiabe
 *
 * Header and MakeFile based on examples from 
 * Peter Zimon https://github.com/peterzimon/pico-toolbox
 * 
 * scale() function based on Arduino map()
 **************************************************/

#pragma once

#include <cstdint>
#include <array>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#define SPI_10_MHZ 10000000
#define SPI_CHANNEL spi0

enum Taper {
    TAPER_A,
    TAPER_B,
    TAPER_C,
    TAPER_W,
    TAPER_M,
    TAPER_N,
    TAPER_CUSTOM,
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
        bool setTaper(Taper taper);
        bool setTaper(uint16_t lower_bounds[4], uint16_t upper_bounds[4]);
        Taper getTaper();

    private:

        uint32_t scale(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max);
        uint16_t taperPosition(uint16_t inputValue, bool write = true);

        uint8_t _select, _address;
        uint16_t _taper_lower[4], _taper_upper[4];
        Taper _taper;


        const uint8_t  _cmd_write     = 0b0000'0000;
        const uint8_t  _cmd_read      = 0b0000'1100;
        const uint8_t  _cmd_increment = 0b0000'0100;
        const uint8_t  _cmd_decrement = 0b0000'1000;
        const uint8_t  _mask_err      = 0b0000'0010;
        const uint16_t _mask_data     = 0b0000'0001'1111'1111;

};
