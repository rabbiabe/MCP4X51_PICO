# MCP4X51_PICO
 Raspberry Pi Pico library for MCP4x51 single and dual digital potentiometers
## Overview and Versions
 This library controls MCP4151 and MCP4251 digital potentiometers. It may work with other models in that line but has not been tested. A few general notes:
 - When using a dual potentiometer (MCP4251), each potentiometer should be constructed independently: `DigiPot_MCP4x51 pot0, pot1;`. 
 - the `Taper` enumeration represents the desired taper of the potentiometer sweep:
    - `TAPER_A`: Audio Taper, resistance increases slowly at first so that the first 75% of the potentiometer's range accounts for only 40% of total resistance.
    - `TAPER_B`: Linear Taper
    - `TAPER_C`: Reverse Audio Taper, resistance increases rapidly at first so that the first 25% of the potentiometer's range accounts for 60% of total resistance.
    - `TAPER_W`: The first 25% of range follows `TAPER_A` and the last 25% follows `TAPER_C`; The middle 50% has a linear characteristic.

Changelog:
- V1.0 (1/25/24) Initial Version
- V1.1 (2/26/24) Added: functions to set position in addition to directly setting wiper value; tapers; taper and button examples 
## Functions
### bool init(uint8_t pin_cs, uint8_t pot, Taper taper = TAPER_B, uint16_t wiper = 128)
 Initializes the potentiometer. 
 - `pin_cs`: SPI chip select pin. Specifying a pin other than the standard SPI CS pin allows for software control of multiple MCP4x51 devices.
 - `pot`: 0 or 1 for MCP4251, should always be 0 for MCP4151.
 - `taper`: One of the standard tapers (*not* `TAPER_CUSTOM`) enumerated in Taper (see above). If not specified, defaults to `TAPER_B`.
 - `wiper`: Initial wiper position, 0-256. If not specified, defaults to 128.
 
 Returns `true` if successful, false if there is an error setting initial taper or wiper position.
### bool setTaper(Taper taper)
 Sets the active taper to one of the standard tapers (*not* `TAPER_CUSTOM`).
 - `taper`: One of the values enumerated in Taper (see above).
### bool setTaper(uint16_t lower_bounds[4], uint16_t upper_bounds[4])
 Sets a custom taper. There are four position segments in each taper (0-249; 250-499; 500-749; 750-1000) and corresponding upper and lower bounds of resistance for each segment, specified in 0.1% increments of total resistance (values 0-1000).
 - `lower_bounds`: array of values (0-1000) representing the lower bounds of each segment, beginning with the 0-249 segment.
 - `upper_bounds`: array of values (0-1000) representing the upper bounds of each segment, beginning with the 0-249 segment.

 Returns `true` if successful, false for error.
### Taper getTaper()
 Returns the currently selected taper.
### bool increment()
 Increases the wiper position by one step, will hold at maximum.
 
 Returns `true` if successful, false for error.
### bool decrement()
 Decreases the wiper position by one step, will hold at minimum.
 
 Returns `true` if successful, false for error.
### bool writeValue(uint16_t value)
 Sets the potentiometer to a raw wiper value 0-256. This method ignores any taper and always sets the potentiometer to the specified value.
 - `value`: The potentiometer setting.
 
 Returns `true` if successful, false for error.
### bool writePosition(uint16_t thousandths)
 Sets the potentiometer to a relative position between CCW and CW, in 0.1% increments (values 0-1000). This value is tapered before setting the potentiometer according to the taper value set by `init()` or `setTaper()`.
 
 Returns `true` if successful, false for error.
### int16_t readValue()
 Returns the current raw wiper value 0-256 for the potentiometer if successful, -1 for error.
### int16_t readPosition()
 Returns the current relative position of the potentiometer between CCW and CW, in 0.1% increments (values 0-1000), -1 for error. The tapering is "unwound" before returning, so the output value is relative to wiper travel, not total resistance. To read the exact resistance, regardless of taper, use readValue().
