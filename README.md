# MCP4X51_PICO
 Raspberry Pi Pico library for MCP4x51 single and dual digital potentiometers
## Overview
 This library controls MCP4151 and MCP4251 digital potentiometers. It may work with other models in that line but has not been tested. A few general notes:
 - When using a dual potentiometer (MCP4251), each potentiometer should be constructed independently: `DigiPot_MCP4x51 pot0, pot1;`. 
 - the `Taper` enumeration represents the desired taper of the potentiometer sweep:
    - `TAPER_A`: Audio Taper, resistance increases slowly at first so that the first 75% of the potentiometer's range accounts for only 40% of total resistance.
    - `TAPER_B`: Linear Taper
    - `TAPER_C`: Reverse Audio Taper, resistance increases rapidly at first so that the first 25% of the potentiometer's range accounts for 60% of total resistance.
    - `TAPER_W`: The first 25% of range follows `TAPER_A` and the last 25% follows `TAPER_C`; The middle 50% has a linear characteristic.
## Functions
### bool init(uint8_t pin_cs, uint8_t pot, Taper taper = TAPER_B, uint16_t wiper = 128)

### void setTaper(Taper taper)
### Taper getTaper()
### bool increment()
### bool decrement()
### bool writeValue(uint16_t value)
### bool writePosition(uint16_t thousandths)
### int16_t readValue()
### int16_t readPosition()
