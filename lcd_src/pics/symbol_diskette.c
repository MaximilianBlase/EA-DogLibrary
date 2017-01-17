/*
 * author: Maximilian Blase
 * date:   20.02.16
 */

#include <avr/pgmspace.h>
#include "../drawing/drawingFigures.h"

// width = 16
// height = 2*8 = 2 << 3

const uint8_t symbol_diskette_data[] PROGMEM = {
        0xFF, 0x01, 0x01, 0x01, 0x1F, 0x11, 0x15, 0x15, 0x11, 0x11, 0x11, 0x1F, 0x02, 0x04, 0x08, 0xF0,
        0xFF, 0x80, 0x80, 0x80, 0x95, 0x95, 0x95, 0x95, 0x95, 0x95, 0x95, 0x85, 0x80, 0x80, 0x80, 0xFF,
};

const imageData_t symbol_diskette = {symbol_diskette_data, 16, 2 << 3}; // Multiply by 8