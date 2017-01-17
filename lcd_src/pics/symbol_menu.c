/*
 * author: Maximilian Blase
 * date:   20.02.16
 */

#include <avr/pgmspace.h>
#include "../drawing/drawingFigures.h"

// width = 16
// height = 2*8 = 2 << 3

const uint8_t symbol_menu_data[] PROGMEM = {
        0xF0,0x96,0x96,0xF0,0xB4,0xB4,0xB4,0xB4,0xB4,0xB4,0xB4,0xB4,0xB4,0xF4,0xF4,0xF0,
        0x00,0x66,0x66,0x00,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x00,0x00,0x00,
};

const imageData_t symbol_menu = {symbol_menu_data, 16, 2 << 3}; // Multiply by 8