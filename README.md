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
 Initializes the potentiometer. 
 - `pin_cs`: SPI chip select pin. Specifying a pin other than the standard SPI CS pin allows for software control of multiple MCP4x51 devices.
 - `pot`: 0 or 1 for MCP4251, should always be 0 for MCP4151.
 - `taper`: One of the values enumerated in Taper (see above). If not specified, defaults to `TAPER_B`.
 - `wiper`: Initial wiper position, 0-256. If not specified, defaults to 128.
 
 Returns `true` if successful.
### void setTaper(Taper taper)
 Changes the active taper.
 - `taper`: One of the values enumerated in Taper (see above).
### Taper getTaper()
 Returns the currently selected taper.
### bool increment()
 Increases the wiper position by one step, will hold at maximum.
 
 Returns `true` if successful.
### bool decrement()
 Decreases the wiper position by one step, will hold at minimum.
 
 Returns `true` if successful.
### bool writeValue(uint16_t value)
 Sets the potentiometer to a raw index value 0-256. This method ignores any taper and always sets the potentiometer to the specified value.
 - `value`: The potentiometer setting.
 
 Returns `true` if successful.
### bool writePosition(uint16_t thousandths)
 Sets the potentiometer to a relative position between CCW and CW, in 0.1% increments. This value is tapered before setting the potentiometer according to the taper value set by `init()` or `setTaper()`.
 
 Returns `true` if successful.
### int16_t readValue()
 Returns the current raw index value 0-256 for the potentiometer.
### int16_t readPosition()
 Returns the current relative position of the potentiometer between CCW and CW, in 0.1% increments.
