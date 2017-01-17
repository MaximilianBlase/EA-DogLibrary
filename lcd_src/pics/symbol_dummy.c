/*
 * author: Maximilian Blase
 * date:   20.02.16
 */

#include <avr/pgmspace.h>
#include "../drawing/drawingFigures.h"

// width = 16
// height = 2*8 = 2 << 3

const uint8_t symbol_dummy_data[0] PROGMEM = {};

const imageData_t symbol_dummy = {symbol_dummy_data, 0, 0}; // Multiply by 8