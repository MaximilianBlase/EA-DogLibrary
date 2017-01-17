/*! @file drawingDotsAndLines.h
 *
 * @author Maximilian Blase
 * @date 2016-02-18
 *
 * @date 2016-02-19
 * @note This file implements abstract graphic functions based on dogm128-graphic.h, like line, dot eg. This figures
 * start at a given coordinate point defined in drawingDotsAndLines.h as a complex struct. The figures will be printed
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

//TODO: Implement big lines

#ifndef MCU_DRAWINGDOTSANDLINES_H
#define MCU_DRAWINGDOTSANDLINES_H

#include <avr/io.h>
#include "drawingUtilities.h"

/*******************************************************************************
 * coordinate system
 *******************************************************************************
 * actual dogm display
 * x/y coordinate system
 * beginning with x=0 and y=0 on top left
 * only positive numbers
 * height in y direction from 0 to 64
 * width in x direction from 0 to 128
 */

/*******************************************************************************
 * dots
 ******************************************************************************/

/*! @brief draw a small dot
 *
 * @param point coordinate point
 *
 * This function draws a 1by1 dot on the screen.
 */
void draw_figure_dotSmall(coordinatePoint_t point);

/*! @brief draw a big dot
 *
 * @param point coordinate point
 *
 * This function draws a 3by3 dot filled on the screen.
 */
void drawfigure_dotBig(coordinatePoint_t point);

/*******************************************************************************
 * lines
 ******************************************************************************/

/*! @brief define line types
 *
 * @param DRAW_LINE_FILLED
 * @param DRAW_LINE_DOTTED
 * @PARAM DRAW_LINE_DASHED
 *
 * This enum defines different line types.
 */
typedef enum {
    DRAW_LINE_FILLED,
    DRAW_LINE_DOTTED,
    DRAW_LINE_DASHED
} draw_figure_line_t;

/*! @brief draw a horizontal line
 *
 * @param startPoint    coordinate point to start the line
 * @param length        length in pixel of the line
 * @param type          define line type
 *
 * This function draws a filled 1px line from the given start_point in horizontal direction of the given pixel length.
 */
void draw_figure_lineHorizontal(coordinatePoint_t startPoint, uint8_t length, draw_figure_line_t type);

/*! @brief draw a vertical line
 *
 * @param startPoint    coordinate point to start the line
 * @param length        length in pixel of the line
 * @param type          define line type
 *
 * This function draws a filled 1px line from the given start_point in vertical direction of the given pixel length.
 */
void draw_figure_lineVertical(coordinatePoint_t startPoint, uint8_t length, draw_figure_line_t type);

/*! @brief draw a line with angle
 *
 * @param startPoint    coordinate point to start the line
 * @param endPoint      coordinate point to end the line
 * @param type          define line type
 *
 * This function draws a filled 1px line from the given start_point to the given end_point. The coordinate points can be
 * anywhere in the coordinate system. There can be an angle between them.
 */
void draw_figure_lineCoordinates(coordinatePoint_t startPoint, coordinatePoint_t endPoint, draw_figure_line_t type);

/*******************************************************************************
 * arrows
 ******************************************************************************/

/*! @brief define arrow types
 *
 * @param DRAW_ARROW_NO_ARROW   draw no arrow
 * @param DRAW_ARROW_FILLED     draw filled arrow
 * @param DRAW_ARROW_OUTLINE    draw outline arrow
 *
 * This enum defines different arrow types
 */
typedef enum {
    DRAW_ARROW_NO_ARROW,
    DRAW_ARROW_FILLED,
    DRAW_ARROW_OUTLINE
} draw_figure_arrow_t;

/*! @brief draw horizontal arrow
 *
 * @param startPoint    coordinate point to start the arrow
 * @param length        length in pixel of the arrow
 * @param lineType      define line type
 *
 * This function draws a 1px arrow from the given start_point in horizontal direction of the given pixel length. The
 * types of line and arrows can be specified.
 */
void draw_figure_arrowHorizontal(coordinatePoint_t startPoint, uint8_t length, draw_figure_line_t lineType,
                                 draw_figure_arrow_t startArrowType, draw_figure_arrow_t endArrowType);

/*! @brief draw vertical arrow
 *
 * @param startPoint    coordinate point to start the arrow
 * @param length        length in pixel of the arrow
 * @param lineType      define line type
 *
 * This function draws a 1px arrow from the given start_point in vertical direction of the given pixel length. The
 * types of line and arrows can be specified.
 */
void draw_figure_arrowVertical(coordinatePoint_t startPoint, uint8_t length, draw_figure_line_t lineType,
                               draw_figure_arrow_t startArrowType, draw_figure_arrow_t endArrowType);

#endif //MCU_DRAWINGDOTSANDLINES_H