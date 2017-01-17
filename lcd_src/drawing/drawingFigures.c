/*! @file drawingFigures.c
 *
 * @author Maximilian Blase
 * @date 2016-02-19
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

#include "drawingFigures.h"
#include "../dogm128-graphic.h"

inline void draw_figure_turnCoordinatePoints(coordinatePoint_t *startPoint, coordinatePoint_t *endPoint) {
    if (startPoint->x > endPoint->x) {
        uint8_t tmp = endPoint->x;
        endPoint->x = startPoint->x;
        startPoint->x = tmp;
    }
    if (startPoint->y > endPoint->y) {
        uint8_t tmp = endPoint->y;
        endPoint->y = startPoint->y;
        startPoint->y = tmp;
    }
}


void draw_figure_cross(coordinatePoint_t startPoint, coordinatePoint_t endPoint) {
    draw_figure_turnCoordinatePoints(&startPoint, &endPoint);

    // top left to low right
    draw_figure_lineCoordinates(startPoint, endPoint, DRAW_LINE_FILLED);

    // low left to top right
    coordinatePoint_t lowLeft = {startPoint.x, endPoint.y};
    coordinatePoint_t topRight = {endPoint.x, startPoint.y};
    draw_figure_lineCoordinates(lowLeft, topRight, DRAW_LINE_FILLED);
}

void draw_figure_rectangleFilled(coordinatePoint_t startPoint, coordinatePoint_t endPoint) {
    draw_figure_turnCoordinatePoints(&startPoint, &endPoint);

    dogmGraphic_drawArea(startPoint.x, startPoint.y, (endPoint.x - startPoint.x) + 1,
                         (endPoint.y - startPoint.y) + 1, DOGM_ADD);
}

void draw_figure_rectangleOutline(coordinatePoint_t startPoint, coordinatePoint_t endPoint) {
    draw_figure_turnCoordinatePoints(&startPoint, &endPoint);

    coordinatePoint_t leftButtom = {startPoint.x, endPoint.y};
    coordinatePoint_t rightTop = {endPoint.x, startPoint.y};

    draw_figure_lineHorizontal(startPoint, (endPoint.x - startPoint.x) + 1, DRAW_LINE_FILLED);
    draw_figure_lineHorizontal(leftButtom, (endPoint.x - startPoint.x) + 1, DRAW_LINE_FILLED);

    draw_figure_lineVertical(startPoint, (endPoint.y - startPoint.y) + 1, DRAW_LINE_FILLED);
    draw_figure_lineVertical(rightTop, (endPoint.y - startPoint.y) + 1, DRAW_LINE_FILLED);
}

void draw_figure_circleFilled(coordinatePoint_t middle, uint8_t radius) {
    dogmGraphic_drawCircleOutline(middle.x, middle.y, radius, 1);
}

void draw_figure_circleOutline(coordinatePoint_t middle, uint8_t radius) {
    dogmGraphic_drawCircleOutline(middle.x, middle.y, radius, 0);
}

void draw_figure_triangleOutline(coordinatePoint_t coordinateA, coordinatePoint_t coordinateB,
                                 coordinatePoint_t coordinateC) {
    draw_figure_lineCoordinates(coordinateA, coordinateB, DRAW_LINE_FILLED);
    draw_figure_lineCoordinates(coordinateB, coordinateC, DRAW_LINE_FILLED);
    draw_figure_lineCoordinates(coordinateC, coordinateA, DRAW_LINE_FILLED);
}

void draw_figure_image(coordinatePoint_t startPoint, imageData_t data, uint8_t clean, dogmGraphic_drawType_t type) {
    if (clean || (type == DOGM_CLEAR)) {
        // clean area
        dogmGraphic_drawArea(startPoint.x, startPoint.y, data.width, data.height, DOGM_CLEAR);
    }

    dogmGraphic_drawP(startPoint.x, startPoint.y, data.width, data.height, type, data.datapath);
}