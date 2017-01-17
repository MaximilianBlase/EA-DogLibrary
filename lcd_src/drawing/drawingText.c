/*! @file drawingText.h
 *
 * @author Maximilian Blase
 * @date 2016-02-20
 *
 * @date 2016-02-21
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

// TODO make a difference between inverted (what is done here) and invert, where "invert" is an XOR with the font
// See line 61

#include <avr/io.h>
#include "drawingText.h"
#include "drawingFigures.h"

uint8_t draw_font_char(dogmGraphic_drawType_t type, char letter) {

    // get width of char
    uint8_t width = draw_font_getCharWidth(letter);

    if (
            !(dogmGraphic_testWidth(draw_font_actualCursor.x + width)) ||
            !(dogmGraphic_testHeight(draw_font_actualCursor.y + draw_font_actualFont->char_height))
        ) {
        // return, if it is not possible to draw complete char on screen
        return 0;
    };

    if (
            (letter < draw_font_actualFont->char_first_of_ascii) ||
            (letter > draw_font_actualFont->char_last_of_ascii) ||
            ((draw_font_actualCursor.x + width) > draw_font_actualCursor.lineEnd)
            ) {
        // return, if char is not in given font table,
        // or if the lineEnd would be reached
        return 0;
    }

    // calculate position of font data in flash
    uint16_t delta = 0;
    for (uint8_t j = 0; j < (letter - draw_font_actualFont->char_first_of_ascii); ++j) {
        delta += pgm_read_byte(draw_font_actualFont->data_delta_width + j);
    }

    if (type == DOGM_INVERT) {
        dogmGraphic_drawArea(
                draw_font_actualCursor.x - 1,
                draw_font_actualCursor.y - 1,
                width + draw_font_actualFont->char_space_horizontal,
                draw_font_actualFont->char_height + 2,
                DOGM_SET
        );
    }

    draw_figure_image(
            (coordinatePoint_t) {
                    draw_font_actualCursor.x,
                    draw_font_actualCursor.y
            },
            (imageData_t) {
                    draw_font_actualFont->data_font + (delta * (draw_font_actualFont->char_height >> 3)), //divide by 8
                    width,
                    draw_font_actualFont->char_height
            },
            0,
            type
    );

    // increment position
    uint8_t totalCharWidth = width + draw_font_actualFont->char_space_horizontal;
    draw_font_actualCursor.x += totalCharWidth;

    return totalCharWidth;
}


void draw_font_stringCoordinate(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, char* string) {
    // settings
    draw_font_setCursorCoordinate(startPoint);

    draw_font_string(type, string);
}

void draw_font_string(dogmGraphic_drawType_t type, char* string) {
    while (*string != 0) {
        if (draw_font_findNewLine(*string)) {
            draw_font_newLine();
        }
        else {
            draw_font_char(type, *string);
        }
        string++;
    }
}

void draw_font_stringAligned(dogmGraphic_drawType_t type, char* string, draw_font_alignment_t alignment) {

    // at first, calculate length
    uint8_t stringLength = 0;
    char currentChar;
    char* currentCharPos = string;
    do {

        currentChar = *currentCharPos;

        // when newline is found, draw everything to there
        if (draw_font_findNewLine(currentChar) || !currentChar) {

            if (stringLength > draw_font_actualFont->char_space_horizontal) {
                stringLength -= draw_font_actualFont->char_space_horizontal;
            }
            draw_font_correctAlignment(alignment, stringLength);
            stringLength = 0; // reset length for next line

            // print current line
            while (*string) {

                if (draw_font_findNewLine(*string)) {
                    // break printing on newline character
                    draw_font_newLine();
                    string++;
                    break;
                }

                draw_font_char(type, *string);
                string++;
            }
        }
        else { // do not get length for '\n' and '\0'
            stringLength += draw_font_getCharWidth(currentChar);
            stringLength += draw_font_actualFont->char_space_horizontal;
        }

        currentCharPos++;
    }
    while (currentChar);
}

void draw_font_stringCoordinateP(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, const char* string) {
    // settings
    draw_font_setCursorCoordinate(startPoint);

    draw_font_stringP(type, string);
}

void draw_font_stringAlignedP(dogmGraphic_drawType_t type, const char* string, draw_font_alignment_t alignment) {

    // at first, calculate length
    uint8_t currentChar, stringLength = 0;
    const char* currentStringPos = string;
    do {

        currentChar = pgm_read_byte(currentStringPos);
        currentStringPos++;

        // when newline is found, draw everything to there
        if (draw_font_findNewLine((char) currentChar) || !currentChar) {

            if (stringLength > draw_font_actualFont->char_space_horizontal) {
                stringLength -= draw_font_actualFont->char_space_horizontal;
            }
            draw_font_correctAlignment(alignment, stringLength);
            stringLength = 0; // reset length for next line

            uint8_t currentPrintChar;
            // print current line
            while ((currentPrintChar = pgm_read_byte(string))) {

                string++;

                if (draw_font_findNewLine((char) currentPrintChar)) {
                    // break printing on newline character
                    draw_font_newLine();
                    break;
                }

                draw_font_char(type, (char) currentPrintChar);
            }
        }
        else {
            stringLength += draw_font_getCharWidth((char) currentChar);
            stringLength += draw_font_actualFont->char_space_horizontal;
        }


    }
    while (currentChar);
}

void draw_font_stringP(dogmGraphic_drawType_t type, const char* string) {
    uint8_t currentChar = pgm_read_byte(string);
    while (currentChar != 0) {
        if (draw_font_findNewLine((char) currentChar)) {
            draw_font_newLine();
        }
        else {
            draw_font_char(type, (char) currentChar);
        }
        string++;
        currentChar = pgm_read_byte(string);
    }
}