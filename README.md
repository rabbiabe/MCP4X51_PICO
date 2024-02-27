# MCP4X51_PICO
 Raspberry Pi Pico library for MCP4x51 single and dual digital potentiometers
## Overview
 This library controls MCP4151 and MCP4251 digital potentiometers. It may work with other models in that line but has not been tested. When using a dual potentiometer (MCP4251), each potentiometer should be constructed independently: `DigiPot_MCP4x51 pot0, pot1;`
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
