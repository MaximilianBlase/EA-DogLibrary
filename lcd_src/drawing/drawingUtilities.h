/*! @file drawingUtilities.h
 *
 * @author Maximilian Blase
 * @date 2016-06-07
 *
 * @date 2016-06-07
 * @note This file implements font utility functions based on dogm128-graphic.h.
 *
 * Please look detailed on the coordinate system starting in X=0 and Y=0 and going positive in right, down direction.
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

#ifndef MCU_DRAWINGUTILITIES_H
#define MCU_DRAWINGUTILITIES_H

#include <avr/io.h>
#include <avr/pgmspace.h>

/*******************************************************************************
 * coordinate system
 *******************************************************************************
 * dogm128 display
 * x/y coordinate system
 * beginning with x=0 and y=0 on top left
 * only positive numbers
 * height in y direction from 0 to 64
 * width in x direction from 0 to 128
 */

/*! @brief point in x/y coordinate system
 *
 * @param x part in horizontal direction; only positive
 * @param y part in vertical direction; only positive
 *
 * This struct represents a coordinate point in an x/y coordinate system where x is the horizontal direction an y the
 * vertical. The coordinate system is starting in point X=0, y=0 in the top left corner an is going positive through
 * right and down. Negative coordinate points are not possible. The maximum number is 255.
 */
typedef struct {
    uint8_t x;
    uint8_t y;
} coordinatePoint_t;

/*! @brief struct to store font data infos
 *
 * @param data_font             start adress on the flash of real font data array
 * @param data_delta_width      start adress on the flash of font width array; representing the width information of
 *                              every char
 * @param char_height           maximum height in px of a char
 * @param char_first_of_ascii   number in ascii_table of first char in font data array
 * @param char_last_of_ascii    number in ascii_table of last char in font data array
 * @param char_space_horizontal space between chars in horizontal direction
 * @param char_space_vertical   space between chars in vertical direction
 *
 * This struct contains general information about a font in flash mem. This information are needed in every function
 * which is drawing font data.
 */
typedef struct {
    PGM_VOID_P data_font;
    PGM_VOID_P data_delta_width;
    uint8_t char_height;
    uint8_t char_first_of_ascii;
    uint8_t char_last_of_ascii;
    uint8_t char_space_horizontal;
    uint8_t char_space_vertical;
} fontData_t;

/*! @brief font alignment
 *
 * @param DRAW_ALIGNMENT_LEFT       start font on coordinate point
 * @param DRAW_ALIGNMENT_RIGHT      end font on coordinate point
 * @param DRA_ALIGNMENT_CENTERED    center font on coordinate point
 *
 * This enum defines values, to align the given string, or number to the given coordinate point.
 */
typedef enum FontAlignment {
    DRAW_ALIGNMENT_LEFT,
    DRAW_ALIGNMENT_RIGHT,
    DRAW_ALIGNMENT_CENTERED
} draw_font_alignment_t;

/*! @brief actual font infos
 *
 * This pointer stores the actual font with all its infos. Every function uses this font to draw its chars.
 */
const fontData_t* draw_font_actualFont;

/*! @brief cursor infos
 *
 * This struct contains all information about an cursor on a screen. Some functions start drawing at the cursor pos and
 * then count them up. The cursor pos is also used for new lines to start at the correct place.
 */
typedef struct Cursor {
    uint8_t x;
    uint8_t y;
    uint8_t lineStart;
    uint8_t lineEnd;
} cursor_t;

/*!
 * @brief actual cursor in ram
 *
 * This value stores the actual used cursor.
 */
cursor_t draw_font_actualCursor;

/*! @brief sets the cursor
 *
 * @param x     horizontal position in px
 * @param y     vertical position in px
 *
 * This function sets the used cursor at a new place defined over the given values x and y. The values will be tested
 * first before updating the cursor.
 */
void draw_font_setCursorXY(uint8_t x, uint8_t y);


/*! @brief sets the cursor
 *
 * @param x     horizontal position in px
 *
 * This function sets the used cursor at a new x position. The value will be tested
 * first before updating the cursor.
 */
void draw_font_setCursorX(uint8_t x);


/*! @brief sets the cursor
 *
 * @param y     vertical position in px
 *
 * This function sets the used cursor at a new y position. The value will be tested
 * first before updating the cursor.
 */
void draw_font_setCursorY(uint8_t y);

/*! @brief sets the cursor
 *
 * @param point new coordinate point
 *
 * This function sets the used cursor at a new place defined over the given point value. The value will be tested first
 * before updating the cursor.
 */
void draw_font_setCursorCoordinate(coordinatePoint_t point);

/*! @brief set the right border
 *
 * @param lineEnd   specifies the right border
 *
 * This function updates the right border. No font function will draw behind this border. Use it very well.
 */
void draw_font_setCursorLineEnd(uint8_t lineEnd);

/*! @brief set the new font
 *
 * @param newFont   specifies the new font
 *
 * This function updates the used font. Every font function draws with this font. It sets the global value.
 */
void draw_font_setFont(const fontData_t* newFont);

/*! @brief sets cursor to a new line
 *
 * This function sets the actual cursor to the beginning of a line in horizontal direction and set the vertical pos to
 * the next line using the char height in the given font. The function won't change the line, if there is not enough
 * vertical space for the next line.
 */
void draw_font_newLine(void);

/*! @brief get the count of the string
 *
 * @param string            string to count chars
 *
 * @return                  number of chars in string
 *
 * This inline function counts the number of chars in the given string and returns them.
 */
uint8_t draw_font_getStringCount(char* string);

/*! @brief find char width of char in font
 *
 * @param letter    char of searched width
 *
 * @return  width of searched char
 *
 * This inline function returns the width of a given char in a given font.
 */
uint8_t draw_font_getCharWidth(char letter);

/*! @brief get string width
 *
 * @param string    string to get width of
 *
 * @return width of given string
 *
 * This function returns the width of the given string.
 */
uint8_t draw_font_getStringWidth(char* string);

/*! @brief correct font start position
 *
 * @param alignment draw_font_alignment_t
 * @param width     actual string width
 *
 * This function corrects the actual cursor position for the actual alignment with the actual string width.
 */

void draw_font_correctAlignment(draw_font_alignment_t alignment, uint8_t stringWidth);

/*! @brief search newLine char
 *
 * @param letter    char to compare
 *
 * This inline function returns true, if the given char is a newLine char, otherwise returns false.
 */
uint8_t draw_font_findNewLine(char letter);

#endif //MCU_DRAWINGUTILITIES_H
