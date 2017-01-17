/*! @file drawingNumbers.h
 *
 * @author Maximilian Blase
 * @date 2016-06-07
 *
 * @date 2016-06-07
 *
 * #####################################################################################################################
 * @Copyright (c) 2016, M.Blase, info@maximilian-blase.de
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 * following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * #####################################################################################################################
 */

#include <stdlib.h>
#include "drawingNumbers.h"
#include "drawingText.h"

void draw_font_numberInt16Coordinate(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, int16_t number,
                                     uint8_t base, draw_font_alignment_t alignment) {
    // settings
    draw_font_setCursorCoordinate(startPoint);

    draw_font_numberInt16(type, number, base, alignment);
}

void draw_font_numberInt16(dogmGraphic_drawType_t type, int16_t number, uint8_t base, draw_font_alignment_t alignment) {
    char string[7];
    itoa(number, string, base);

    draw_font_correctAlignment(alignment, draw_font_getStringWidth(string));
    draw_font_string(type, string);
}

void draw_font_numberUint16Coordinate(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, uint16_t number,
                                      uint8_t base, draw_font_alignment_t alignment) {
    // settings
    draw_font_setCursorCoordinate(startPoint);

    draw_font_numberUint16(type, number, base, alignment);
}

void draw_font_numberUint16(dogmGraphic_drawType_t type, uint16_t number, uint8_t base,
                            draw_font_alignment_t alignment) {
    char string[6];
    utoa(number, string, base);

    draw_font_correctAlignment(alignment, draw_font_getStringWidth(string));
    draw_font_string(type, string);
}

void draw_font_numberUint16FixedCoordinate(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, uint16_t number,
                                           uint8_t widthBehindDot, uint8_t base, draw_font_alignment_t alignment) {
    // settings
    draw_font_setCursorCoordinate(startPoint);

    draw_font_numberUint16Fixed(type, number, widthBehindDot, base, alignment);
}

void draw_font_numberUint16Fixed(dogmGraphic_drawType_t type, uint16_t number, uint8_t widthBehindDot, uint8_t base,
                                 draw_font_alignment_t alignment) {
    if (widthBehindDot > 5) { //maximum of 5 degrees behind the dot
        widthBehindDot = 5;
    }
    char string[7] = {0, 0, 0, 0, 0, 0, 0};
    utoa(number, string, base);
    uint8_t length = draw_font_getStringCount(&string[0]);

    if (length <= widthBehindDot) { //correct length of string with shifting
        while (length <= widthBehindDot) {
            for (uint8_t i = 6; i > 0; --i) {
                string[i] = string[i - 1];
            }
            string[0] = '0';
            length++;
        }
    }

    for (int8_t i = length; i > (length - widthBehindDot - 1); i--) { //correct length of string for dot
        string[i + 1] = string[i];
    }
    string[length - widthBehindDot] = '.';

    draw_font_correctAlignment(alignment, draw_font_getStringWidth(string));
    draw_font_string(type, string);
}

void draw_font_numberInt32Coordinate(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, int32_t number,
                                     uint8_t base, draw_font_alignment_t alignment) {
    // settings
    draw_font_setCursorCoordinate(startPoint);

    draw_font_numberInt32(type, number, base, alignment);
}

void draw_font_numberInt32(dogmGraphic_drawType_t type, int32_t number, uint8_t base, draw_font_alignment_t alignment) {
    char string[13];
    ltoa(number, string, base);

    draw_font_correctAlignment(alignment, draw_font_getStringWidth(string));
    draw_font_string(type, string);
}

void draw_font_numberUint32Coordinate(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, uint32_t number,
                                      uint8_t base, draw_font_alignment_t alignment) {
    // settings
    draw_font_setCursorCoordinate(startPoint);

    draw_font_numberUint32(type, number, base, alignment);
}

void draw_font_numberUint32(dogmGraphic_drawType_t type, uint32_t number, uint8_t base,
                            draw_font_alignment_t alignment) {
    char string[12];
    ultoa(number, string, base);

    draw_font_correctAlignment(alignment, draw_font_getStringWidth(string));
    draw_font_string(type, string);
}