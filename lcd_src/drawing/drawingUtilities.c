/*! @file drawingUtilities.h
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

#include "drawingUtilities.h"
#include "../dogm128-graphic.h"


inline void draw_font_setCursorXY(uint8_t x, uint8_t y) {
    draw_font_setCursorX(x);
    draw_font_setCursorY(y);
}

inline void draw_font_setCursorX(uint8_t x) {
    if (!dogmGraphic_testWidth(x)) {
        return;
    }

    draw_font_actualCursor.x = x;
    draw_font_actualCursor.lineStart = x;
}

inline void draw_font_setCursorY(uint8_t y) {
    if (!dogmGraphic_testHeight(y)) {
        return;
    }

    draw_font_actualCursor.y = y;
}

inline void draw_font_setCursorCoordinate(coordinatePoint_t point) {
    draw_font_setCursorXY(point.x, point.y);
}

inline void draw_font_setCursorLineEnd(uint8_t lineEnd) {
    if (lineEnd < DOGM_DISPLAY_WIDTH) {
        draw_font_actualCursor.lineEnd = lineEnd;
    }
}

inline void draw_font_setFont(const fontData_t* newFont) {
    draw_font_actualFont = newFont;
}

inline void draw_font_newLine(void) {
    uint8_t delta_height = draw_font_actualFont->char_height >> 2; // divide by 4

    if ((draw_font_actualCursor.y + delta_height) >= DOGM_DISPLAY_HEIGHT) {
        return;
    }
    else {
        draw_font_actualCursor.y += (draw_font_actualFont->char_height + draw_font_actualFont->char_space_vertical - 1);
        draw_font_actualCursor.x = draw_font_actualCursor.lineStart;
    }
}

inline uint8_t draw_font_getStringCount(char* string) {
    uint8_t length = 0;

    while (*string != 0) {
        length++;

        string++;
    }
    return length;
}

inline uint8_t draw_font_getCharWidth(char letter) {

    uint8_t width = pgm_read_byte(
            (draw_font_actualFont->data_delta_width + letter) - draw_font_actualFont->char_first_of_ascii
    );
    return width;
}

inline uint8_t draw_font_getStringWidth(char* string) {
    uint8_t length = 0;

    while (*string != 0) {
        length += draw_font_getCharWidth(*string);
        length += draw_font_actualFont->char_space_horizontal;

        string++;
    }
    length -= draw_font_actualFont->char_space_horizontal;

    return length;
}

inline void draw_font_correctAlignment(draw_font_alignment_t alignment, uint8_t stringWidth) {
    switch (alignment) {
        case DRAW_ALIGNMENT_LEFT:
            break;
        case DRAW_ALIGNMENT_RIGHT:
            if (draw_font_actualCursor.x > stringWidth) {
                draw_font_actualCursor.x -= stringWidth;
            }
            break;
        case DRAW_ALIGNMENT_CENTERED:
            stringWidth = stringWidth >> 1; //divided by 2
            if (draw_font_actualCursor.x > stringWidth) {
                draw_font_actualCursor.x -= stringWidth;
            }
            break;
        default:
            break;
    }
}

inline uint8_t draw_font_findNewLine(char letter) {
    return ((uint8_t) letter) == '\n' ? 1 : 0;
}