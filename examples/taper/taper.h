/**************************************************
 * TEMPLATE
 **************************************************/

#ifndef _SRC_MAIN_H
#define _SRC_MAIN_H

/*
 * C++ HEADERS
 */
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <cstring>

/*
 * PICO HEADERS
 */
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"
#include "hardware/adc.h"
#include "hardware/uart.h"

/*
 * PIN DEFINITIONS
 * 
 * CHANGE THESE IF USING OTHER PINS
 */

const uint8_t pinTaperSelect = 6;
const uint8_t pinPot = 26;
const uint8_t pinCIPO = 16;
const uint8_t pinCS = 17;
const uint8_t pinSCK = 18;
const uint8_t pinCOPI = 19;

/*
 * FUNCTION DECLARATIONS
 */
void taperSelect(uint gpio, uint32_t event_mask);

#endif // _SRC_MAIN_H