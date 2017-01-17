/*! @file drawingNumbers.h
 *
 * @author Maximilian Blase
 * @date 2016-06-07
 *
 * @date 2016-06-07
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

#ifndef MCU_DRAWINGNUMBERS_H
#define MCU_DRAWINGNUMBERS_H

#include <avr/io.h>
#include "../dogm128-graphic.h"
#include "drawingUtilities.h"

/*! @brief draw a signed number from ram
 *
 * @param startPoint        coordinate point to start drawing; top left
 * @param type              type to draw the number like add, clear, set or invert; @see dogm128-graphic.h
 * @param number            signed number to draw from ram
 * @param base              base the number should be drawn; mostly 02, 10 or 16
 * @param alignment         alignment of the given number
 *
 * This function draws a given number from ram starting at the given coordinate in the top left corner. Drawing until
 * end or the lineEnd is reached.
 */
void draw_font_numberInt16Coordinate(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, int16_t number,
                                     uint8_t base, draw_font_alignment_t alignment);

/*! @brief draw a signed number from ram
 *
 * @param type              type to draw the number like add, clear, set or invert; @see dogm128-graphic.h
 * @param number            signed number to draw from ram
 * @param base              base the number should be drawn; mostly 02, 10 or 16
 * @param alignment         alignment of the given number
 *
 * This function draws a given number from ram starting at the actual cursor pos in the top left corner. Drawing until
 * end or the lineEnd is reached.
 */
void draw_font_numberInt16(dogmGraphic_drawType_t type, int16_t number, uint8_t base, draw_font_alignment_t alignment);

/*! @brief draw a unsigned number from ram
 *
 * @param startPoint        coordinate point to start drawing; top left
 * @param type              type to draw the number like add, clear, set or invert; @see dogm128-graphic.h
 * @param number            unsigned number to draw from ram
 * @param base              base the number should be drawn; mostly 02, 10 or 16
 * @param alignment         alignment of the given number
 *
 * This function draws a given number from ram starting at the given coordinate in the top left corner. Drawing until
 * end or the lineEnd is reached.
 */
void draw_font_numberUint16Coordinate(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, uint16_t number,
                                      uint8_t base, draw_font_alignment_t alignment);

/*! @brief draw a unsigned number from ram
 *
 * @param type              type to draw the number like add, clear, set or invert; @see dogm128-graphic.h
 * @param number            unsigned number to draw from ram
 * @param base              base the number should be drawn; mostly 02, 10 or 16
 * @param alignment         alignment of the given number
 *
 * This function draws a given number from ram starting at the actual cursor pos in the top left corner. Drawing until
 * end or the lineEnd is reached.
 */
void draw_font_numberUint16(dogmGraphic_drawType_t type, uint16_t number, uint8_t base,
                            draw_font_alignment_t alignment);

/*! @brief draw a double number from ram
 *
 * @param startPoint        coordinate point to start drawing; top left
 * @param type              type to draw the number like add, clear, set or invert; @see dogm-128-graphic.h
 * @param number            unsigned number to draw from ram
 * @param widthBehindDot    digits behind the dot in the number
 * @param base              base the number should be drawn; mostly 02, 10, 16
 * @param alignment         alignment of the given number
 *
 * This function draws a given number from ram starting at the actual cursor pos in the top left corner. Drawing until
 * end or the lineEnd is reached.
 */
void draw_font_numberUint16FixedCoordinate(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, uint16_t number,
                                           uint8_t widthBehindDot, uint8_t base, draw_font_alignment_t alignment);

/*! @brief draw a double number from ram
 *
 * @param type              type to draw the number like add, clear, set or invert; @see dogm-128-graphic.h
 * @param number            unsigned number to draw from ram
 * @param widthBehindDot    digits behind the dot in the number
 * @param base              base the number should be drawn; mostly 02, 10, 16
 * @param alignment         alignment of the given number
 *
 * This function draws a given number from ram starting at the actual cursor pos in the top left corner. Drawing until
 * end or the lineEnd is reached.
 */
void draw_font_numberUint16Fixed(dogmGraphic_drawType_t type, uint16_t number, uint8_t widthBehindDot, uint8_t base,
                                 draw_font_alignment_t alignment);

/*! @brief draw a signed number from ram
 *
 * @param startPoint        coordinate point to start drawing; top left
 * @param type              type to draw the number like add, clear, set or invert; @see dogm128-graphic.h
 * @param number            signed number to draw from ram
 * @param base              base the number should be drawn; mostly 02, 10 or 16
 * @param alignment         alignment of the given number
 *
 * This function draws a given number from ram starting at the given coordinate in the top left corner. Drawing until
 * end or the lineEnd is reached.
 */
void draw_font_numberInt32Coordinate(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, int32_t number,
                                     uint8_t base, draw_font_alignment_t alignment);

/*! @brief draw a signed number from ram
 *
 * @param type              type to draw the number like add, clear, set or invert; @see dogm128-graphic.h
 * @param number            signed number to draw from ram
 * @param base              base the number should be drawn; mostly 02, 10 or 16
 * @param alignment         alignment of the given number
 *
 * This function draws a given number from ram starting at the actual cursor pos in the top left corner. Drawing until
 * end or the lineEnd is reached.
 */
void draw_font_numberInt32(dogmGraphic_drawType_t type, int32_t number, uint8_t base, draw_font_alignment_t alignment);

/*! @brief draw a unsigned number from ram
 *
 * @param startPoint        coordinate point to start drawing; top left
 * @param type              type to draw the number like add, clear, set or invert; @see dogm128-graphic.h
 * @param number            unsigned number to draw from ram
 * @param base              base the number should be drawn; mostly 02, 10 or 16
 * @param alignment         alignment of the given number
 *
 * This function draws a given number from ram starting at the given coordinate in the top left corner. Drawing until
 * end or the lineEnd is reached.
 */
void draw_font_numberUint32Coordinate(coordinatePoint_t startPoint, dogmGraphic_drawType_t type, uint32_t number,
                                      uint8_t base, draw_font_alignment_t alignment);

/*! @brief draw a unsigned number from ram
 *
 * @param type              type to draw the number like add, clear, set or invert; @see dogm128-graphic.h
 * @param number            unsigned number to draw from ram
 * @param base              base the number should be drawn; mostly 02, 10 or 16
 * @param alignment         alignment of the given number
 *
 * This function draws a given number from ram starting at the actual cursor pos in the top left corner. Drawing until
 * end or the lineEnd is reached.
 */
void draw_font_numberUint32(dogmGraphic_drawType_t type, uint32_t number, uint8_t base,
                            draw_font_alignment_t alignment);

#endif //MCU_DRAWINGNUMBERS_H
