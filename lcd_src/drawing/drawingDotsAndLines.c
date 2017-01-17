/*! @file drawingDotsAndLines.c
 *
 * @author Maximilian Blase
 * @date 2016-02-18
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

#include "drawingDotsAndLines.h"
#include "../dogm128-graphic.h"
#include "drawingFigures.h"

void draw_figure_dotSmall(coordinatePoint_t point) {

    dogmGraphic_drawDot(point.x, point.y);
    //dogmGraphic_drawArea(point.x, point.y, 1, 1, DOGM_ADD);
}

void drawfigure_dotBig(coordinatePoint_t point) {

    dogmGraphic_drawArea(point.x - 1, point.y - 1, 3, 3, DOGM_ADD);
}

void draw_figure_lineHorizontal(coordinatePoint_t startPoint, uint8_t length, draw_figure_line_t type) {

    if (type == DRAW_LINE_FILLED) {
        dogmGraphic_drawArea(startPoint.x, startPoint.y, length, 1, DOGM_ADD);
    }
    else {
        draw_figure_lineCoordinates(
                startPoint,
                (coordinatePoint_t) {startPoint.x + length, startPoint.y},
                type
        );
    }
}

void draw_figure_lineVertical(coordinatePoint_t startPoint, uint8_t length, draw_figure_line_t type) {

    if (type == DRAW_LINE_FILLED) {
        dogmGraphic_drawArea(startPoint.x, startPoint.y, 1, length, DOGM_ADD);
    }
    else {
        draw_figure_lineCoordinates(
                startPoint,
                (coordinatePoint_t) {startPoint.x, startPoint.y + length},
                type
        );
    }
}

void draw_figure_lineCoordinates(coordinatePoint_t startPoint, coordinatePoint_t endPoint, draw_figure_line_t type) {

    dogmGraphic_drawLineXY(startPoint.x, startPoint.y, endPoint.x, endPoint.y, type);
}

void draw_figure_arrowHorizontal(coordinatePoint_t startPoint, uint8_t length, draw_figure_line_t lineType,
                                 draw_figure_arrow_t startArrowType, draw_figure_arrow_t endArrowType) {
    // draw line
    draw_figure_lineHorizontal(
            (coordinatePoint_t) {
                    startPoint.x + 2,
                    startPoint.y
            },
            length - 4,
            lineType
    );

    //startArrow
    switch (startArrowType) {
        case DRAW_ARROW_NO_ARROW:
            //draw no arrow
            break;
        case DRAW_ARROW_FILLED:
            draw_figure_dotSmall((coordinatePoint_t) {startPoint.x + 1, startPoint.y});
        case DRAW_ARROW_OUTLINE:
            draw_figure_triangleOutline(
                    startPoint,
                    (coordinatePoint_t) {
                            startPoint.x + 2,
                            startPoint.y + 2
                    },
                    (coordinatePoint_t) {
                            startPoint.x + 2,
                            startPoint.y - 2
                    }
            );
            break;
        default:;
    }

    //endArrow
    switch (endArrowType) {
        case DRAW_ARROW_NO_ARROW:
            //draw no arrow
            break;
        case DRAW_ARROW_FILLED:
            draw_figure_dotSmall((coordinatePoint_t) {startPoint.x + length - 1, startPoint.y});
        case DRAW_ARROW_OUTLINE:
            draw_figure_triangleOutline(
                    (coordinatePoint_t) {
                            startPoint.x + length - 2,
                            startPoint.y - 2
                    },
                    (coordinatePoint_t) {
                            startPoint.x + length - 2,
                            startPoint.y + 2
                    },
                    (coordinatePoint_t) {
                            startPoint.x + length,
                            startPoint.y
                    }
            );
            break;
        default:;
    }
}

void draw_figure_arrowVertical(coordinatePoint_t startPoint, uint8_t length, draw_figure_line_t lineType,
                               draw_figure_arrow_t startArrowType, draw_figure_arrow_t endArrowType) {
    // draw line
    draw_figure_lineVertical(
            (coordinatePoint_t) {
                    startPoint.x,
                    startPoint.y + 2
            },
            length - 4,
            lineType
    );

    //startArrow
    switch (startArrowType) {
        case DRAW_ARROW_NO_ARROW:
            //draw no arrow
            break;
        case DRAW_ARROW_FILLED:
            draw_figure_dotSmall((coordinatePoint_t) {startPoint.x, startPoint.y + 1});
        case DRAW_ARROW_OUTLINE:
            draw_figure_triangleOutline(
                    startPoint,
                    (coordinatePoint_t) {
                            startPoint.x + 2,
                            startPoint.y + 2
                    },
                    (coordinatePoint_t) {
                            startPoint.x - 2,
                            startPoint.y + 2
                    }
            );
            break;
        default:;
    }

    //endArrow
    switch (endArrowType) {
        case DRAW_ARROW_NO_ARROW:
            //draw no arrow
            break;
        case DRAW_ARROW_FILLED:
            draw_figure_dotSmall((coordinatePoint_t) {startPoint.x, startPoint.y + length - 1});
        case DRAW_ARROW_OUTLINE:
            draw_figure_triangleOutline(
                    (coordinatePoint_t) {
                            startPoint.x - 2,
                            startPoint.y + length - 2
                    },
                    (coordinatePoint_t) {
                            startPoint.x + 2,
                            startPoint.y + length - 2
                    },
                    (coordinatePoint_t) {
                            startPoint.x,
                            startPoint.y + length
                    }
            );
            break;
        default:;
    }
}