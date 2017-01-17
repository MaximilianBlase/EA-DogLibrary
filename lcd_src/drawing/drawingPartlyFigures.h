/*! @file drawingPartlyFigures.h
 *
 * @author Maximilian Blase
 * @date 2016-02-29
 *
 * @date 2016-02-29
 * @note This file implements abstract partly graphic functions based on dogm128-graphic.h, like circle, rectangle eg.
 * This figures start at a given coordinate point defined in drawingDotsAndLines.h as a complex struct. The figures will
 * be printed in an ram array defined as whole byte pages in Y-direction and bits in X-direction. This figures all need
 * a percent value in a scale of 0 to 100 to get filled.
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

// TODO: Implement partly filled rectangle

#ifndef MCU_DRAWINGPARTLYFIGURES_H
#define MCU_DRAWINGPARTLYFIGURES_H

#include "drawingDotsAndLines.h"

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

/*! @brief define filling types
 *
 * @param DRAW_FILLING_FROM_LEFT    filling starts left and ends right
 * @param DRAW_FILLING_FROM_RIGHT   filling starts right and ends left
 * @param DRAW_FILLING_FROM_TOP     filling starts top and ends down
 * @param DRAW_FILLING_FROM_DOWN    filling starts down and ends up
 *
 * This enum defines different types of filling an area on screen.
 */
typedef enum {
    DRAW_FILLING_FROM_LEFT,
    DRAW_FILLING_FROM_RIGHT,
    DRAW_FILLING_FROM_TOP,
    DRAW_FILLING_FROM_DOWN
} draw_figure_fillingType_t;

/*! @brief correct percent value
 *
 * @param percent   value to correct
 * @param maxScale  maximum scale of value
 *
 * This inline function corrects the given value, if it is out of scale of 0 to maxScale.
 */
void draw_figure_correctPercentValue(uint8_t *percent, uint8_t maxScale);

/*! @brief find length value
 *
 * @param maxScale          maximum scale of value
 * @param percentFilled     value in scale of 0 to maxScale
 * @param length            length at maxScale
 *
 * @return                  percent length with given values
 *
 * This inline function detects the actual length with the given percent values to the complete length.
 */
uint8_t draw_figure_generatePercentValue(uint8_t maxScale, uint8_t percentFilled, uint8_t length);

/*! @brief draw a percentile filled rectangle area
 *
 * @param startPoint    first point top left of drawing area
 * @param endPoint      second point low right of drawing area
 * @param maxScale      maximum scale of percent value
 * @param percentFilled number of filled area in a scale of 0 to maxScale
 * @param type          type of the way of filling the area
 *
 * This function draws a partly filled rectangle in the given area on screen in the given type.
 */
void draw_figure_rectangleFilledPercent(coordinatePoint_t startPoint, coordinatePoint_t endPoint, uint8_t maxScale,
                                        uint8_t percentFilled, draw_figure_fillingType_t type);

#endif //MCU_DRAWINGPARTLYFIGURES_H
