/*! @file drawingText.h
 *
 * @author Maximilian Blase
 * @date 2016-02-20
 *
 * @date 2016-02-21
 * @note This file implements abstract font functions based on dogm128-graphic.h, like line, dot eg. This fonts
 * start at a given coordinate point defined in drawingDotsAndLines.h as a complex struct. The fonts will be printed
 * in an ram array defined as whole byte pages in Y-direction and bits in X-direction.
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

//TODO: Implement big fonts
//TODO: Implement cursive fonts
//TODO: Implement cancelled fonts
//TODO: Implement underlined fonts
//TODO: Implement fonts starting != 1st px in height on flash

#ifndef MCU_DRAWINGFONTS_H
#define MCU_DRAWINGFONTS_H

#include <avr/pgmspace.h>
#include "../dogm128-graphic.h"
#include "drawingUtilities.h"

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

/*! @brief draw a single char
 *
 * @param type          type to draw the char like add, clear, set or invert; @see dogm128-graphic.h
 * @param letter        char to draw
 *
 * @return  total drawn width of char and empty space after char
 *
 * This function draws a given char with the actual font at the actual cursor os from the top left corner. The cursor
 * pos will be incremented with the drawn width of the char and the space between the chars, so that the next drawn char
 * can start at the next free char position.
 *
 * @attention Therefore, if the font is bigger then 8px in the height, every char must be lying together in the flash
 * data space. Most font generators won't do this. We wrote a small qt script to change the byte order after generating
 * them with a normal font generator.
 */
uint8_t draw_font_char(dogmGraphic_drawType_t type, char letter);

/*! @brief draw a string from ram
 *
 * @param startPoint        coordinate point to start drawing; top left
 * @param type              type to draw the string like add, clear, set or invert; @see dogm128-graphic.h
 * @param string            string to draw from ram
 *
 * This function draws a given string from ram starting at the given coordinate in the top left corner. Drawing until
 * one char is null or the lineEnd is reached.
 */
void draw_font_stringCoordinate(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, char* string);

/*! @brief draw a string from ram
 *
 * @param type              type to draw the string like add, clear, set or invert; @see dogm128-graphic.h
 * @param string            string to draw from ram
 *
 * This function draws a given string from ram starting at the actual cursor pos in the top left corner. Drawing until
 * one char is null or the lineEnd is reached.
 */
void draw_font_string(dogmGraphic_drawType_t type, char* string);

/*! @brief draw a string from ram
 *
 * @param type              type to draw the string like add, clear, set or invert; @see dogm128-graphic.h
 * @param string            string to draw from ram
 * @param alignment         alignment to be used
 *
 * This function draws a given string from ram starting at a position calculated for the given alignment around the
 * actual position. Drawing until one char is null or the lineEnd is reached.
 */
void draw_font_stringAligned(dogmGraphic_drawType_t type, char* string, draw_font_alignment_t alignment);

/*! @brief draw a string from flash
 *
 * @param startPoint        coordinate point to start drawing; top left
 * @param type              type to draw the string like add, clear, set or invert; @see dogm128-graphic.h
 * @param string            string to draw from flash
 *
 * This function draws a given string from flash starting at the given coordinate in the top left corner. Drawing until
 * one char is null or the lineEnd is reached.
 */
void draw_font_stringCoordinateP(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, const char* string);

/*! @brief draw a string from flash
 *
 * @param type              type to draw the string like add, clear, set or invert; @see dogm128-graphic.h
 * @param string            string to draw from flash
 * @param alignment         alignment to be used
 *
 * This function draws a given string from flash starting at a position calculated for the given alignment around the
 * actual position. Drawing until one char is null or the lineEnd is reached.
 */
void draw_font_stringAlignedP(dogmGraphic_drawType_t type, const char* string, draw_font_alignment_t alignment);

/*! @brief draw a string from flash
 *
 * @param type              type to draw the string like add, clear, set or invert; @see dogm128-graphic.h
 * @param string            string to draw from flash
 *
 * This function draws a given string from flash starting at the actual cursor pos in the top left corner. Drawing until
 * one char is null or the lineEnd is reached.
 */
void draw_font_stringP(dogmGraphic_drawType_t type, const char* string);

#endif //MCU_DRAWINGFONTS_H