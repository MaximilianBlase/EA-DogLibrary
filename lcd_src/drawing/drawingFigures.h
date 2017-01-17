/*! @file drawingFigures.h
 *
 * @author Maximilian Blase
 * @date 2016-02-19
 *
 * @date 2016-02-20
 * @note This file implements abstract graphic functions based on dogm128-graphic.h, like circle, rectangle eg. This
 * figures start at a given coordinate point defined in drawingDotsAndLines.h as a complex struct. The figures will be
 * printed in an ram array defined as whole byte pages in Y-direction and bits in X-direction.
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

//TODO: Implement Triangle filled function
//TODO: Implement Elipse outline function
//TODO: Implement Elipse filled function
//TODO: Implement Circle arcs function with angles

#ifndef MCU_DRAWINGFIGURES_H
#define MCU_DRAWINGFIGURES_H

#include <avr/pgmspace.h>

#include "drawingDotsAndLines.h"
#include "../dogm128-graphic.h"

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

/*! @brief fast coordinate turn
 *
 * @param startPoint    first given coordinate to compare
 * @param endPoint      second given coordinate to compare
 *
 * This function compares two given coordinatePoint_t* values and returns them, that the startPoint will be on the top
 * left and the endPoint on the low right corner of the area.
 */
void draw_figure_turnCoordinatePoints(coordinatePoint_t *startPoint, coordinatePoint_t *endPoint);

/*! @brief draw a small cross
 *
 * @param startPoint    first point top left of drawing area
 * @param endPoint      second point low right of drawing area
 *
 * This function draws a cross with two lines from the top left corner to the low right corner and from the low left
 * corner to the top right corner. The coordinate points will be switched, if they to not compare with top left and low
 * right corner.
 */
void draw_figure_cross(coordinatePoint_t startPoint, coordinatePoint_t endPoint);

/*! @brief draw a 100% filled rectangle
 *
 * @param startPoint    first point top left of drawing area
 * @param endPoint      second point low right of drawing area
 *
 * This function draws a rectangle in the given area from the top left to the low right corner. The space inside the
 * rectangle will be filled completely.
 */
void draw_figure_rectangleFilled(coordinatePoint_t startPoint, coordinatePoint_t endPoint);

/*! @brief draw a outline rectangle
 *
 * @param startPoint    first point top left of drawing area
 * @param endPoint      second point low right of drawing area
 *
 * This function draws a rectangle in the given area from top left to low right. The shown bits inside the drawn area
 * won't be changed, so they will be still visible after drawing in the same way.
 */
void draw_figure_rectangleOutline(coordinatePoint_t startPoint, coordinatePoint_t endPoint);

/*! @brief draw a 100% filled circle
 *
 * @param middle    coordinate point in the middle of the circle
 * @param radius    space from the middle to the outline of a circle
 *
 * This function draws a circle from the given middle with the given radius. The space inside the circle will be filled
 * completely.
 */
void draw_figure_circleFilled(coordinatePoint_t middle, uint8_t radius);

/*! @brief draw a outline circle
 *
 * @param middle    coordinate point in the middle of the circle
 * @param radius    space from the middle to the outline of a circle
 *
 * This function draws a circle form the given middle with the given radius. The space inside the circle won't be
 * changed.
 */
void draw_figure_circleOutline(coordinatePoint_t middle, uint8_t radius);

/*! @brief draw a triangle outline
 *
 * @param coordinateA   math coordinate point A of triangle
 * @param coordinateB   math coordinate point B of triangle
 * @param coordinateC   math coordinate point C of triangle
 *
 * This function draws the outline of a triangle given with the outline coordinate points A,B and C. The triangle can
 * be drawn in every angle position. All coordinates must be on the screen.
 */
void draw_figure_triangleOutline(coordinatePoint_t coordinateA, coordinatePoint_t coordinateB,
                                 coordinatePoint_t coordinateC);

/*******************************************************************************
 * draw persistent data
 ******************************************************************************/

/*! @brief struct to store flash data infos
 *
 * @param datapath  repesent the first flash adress of the drawn data
 * @param width     width in pixel of the given data
 * @param height    height in pixel of the given data
 *
 * This struct represents data information of a specific place in the flash data. For example the place of a logo witch
 * should be drawn on the screen. Therefore the data address, the width and height are necessary.
 */

typedef struct {
    PGM_VOID_P datapath;
    uint8_t width;
    uint8_t height;
} imageData_t;

/*! @brief draw a data block from flash
 *
 * @param startPoint    top left coordinate to start drawing
 * @param data          data information; @see imageData_t
 * @param clean         1=clean area before drawing; 0=only add pixels
 * @param type          set the specific type like add, clear, invert or set; @see dogmGraphic_drawType_t
 *
 * This function draws a generic block of databytes from flash to the screen. This function can be used to draw images,
 * or font chars. See therefore dogm128-graphic.h for more information.
 */

void draw_figure_image(coordinatePoint_t startPoint, imageData_t data, uint8_t clean, dogmGraphic_drawType_t type);

#endif //MCU_DRAWINGFIGURES_H
