/*
 * author: Maximilian Blase
 * date:   20.02.16
 */

#include <avr/pgmspace.h>
#include "../drawing/drawingFigures.h"

// width = 16
// height = 2*8 = 2 << 3

const uint8_t symbol_usbstick_data[] PROGMEM = {
        0x00,0x00,0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x08,0x18,0x3C,0xFE,0x1C,0x08,0x00,
        0x00,0x0C,0x12,0x21,0x48,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x00,0x00,0x00,0x00,
};

const imageData_t symbol_usbstick = {symbol_usbstick_data, 16, 2 << 3}; // Multiply by 8