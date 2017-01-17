/*! @file drawingPartlyFigures.c
 *
 * @author Maximilian Blase
 * @date 2016-02-29
 *
 * @date 2016-02-29
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

#include "drawingPartlyFigures.h"
#include "../dogm128-graphic.h"
#include "drawingFigures.h"
#include "drawingDotsAndLines.h"

inline void draw_figure_correctPercentValue(uint8_t *percent, uint8_t maxScale) {
    if (*percent > maxScale) {
        *percent = maxScale;
    }
}

inline uint8_t draw_figure_generatePercentValue(uint8_t maxScale, uint8_t percentFilled, uint8_t length) {
    //TODO: needs performance improvement at math part
    return ((length * percentFilled) / maxScale);
}

void draw_figure_rectangleFilledPercent(coordinatePoint_t startPoint, coordinatePoint_t endPoint, uint8_t maxScale,
                                        uint8_t percentFilled, draw_figure_fillingType_t type) {
    draw_figure_turnCoordinatePoints(&startPoint, &endPoint);
    dogmGraphic_drawArea(startPoint.x, startPoint.y, endPoint.x, endPoint.y, DOGM_CLEAR);
    draw_figure_rectangleOutline(startPoint, endPoint);

    if (percentFilled == 0) {
        return;
    }
    else if ((endPoint.x - startPoint.x) > 8 && (endPoint.y - startPoint.y) > 8) {
        // this looks nicer in big areas
        startPoint.x += 1;
        startPoint.y += 1;
        endPoint.x -= 1;
        endPoint.y -= 1;
    }

    draw_figure_correctPercentValue(&percentFilled, maxScale);
    coordinatePoint_t startInlineRectangle = {0,0};
    coordinatePoint_t endInlineRectangle = {0,0};
    switch (type) {
        case DRAW_FILLING_FROM_LEFT:
            startInlineRectangle.x = startPoint.x + 1;
            startInlineRectangle.y = startPoint.y + 1;

            endInlineRectangle.x = startPoint.x + 1 +
                                   draw_figure_generatePercentValue(
                                           maxScale,
                                           percentFilled,
                                           endPoint.x - startPoint.x - 2
                                   );
            endInlineRectangle.y = endPoint.y - 1;
            break;
        case DRAW_FILLING_FROM_RIGHT:
            startInlineRectangle.x = startPoint.x - 1 + (endPoint.x - startPoint.x) -
                                     draw_figure_generatePercentValue(
                                             maxScale,
                                             percentFilled,
                                             endPoint.x - startPoint.x - 2
                                     );
            startInlineRectangle.y = startPoint.y + 1;

            endInlineRectangle.x = endPoint.x - 1;
            endInlineRectangle.y = endPoint.y - 1;
            break;
        case DRAW_FILLING_FROM_TOP:
            startInlineRectangle.x = startPoint.x + 1;
            startInlineRectangle.y = startPoint.y + 1;

            endInlineRectangle.x = endPoint.x - 1;
            endInlineRectangle.y = startPoint.y + 1 +
                                   draw_figure_generatePercentValue(
                                           maxScale,
                                           percentFilled,
                                           endPoint.y - startPoint.y - 2
                                   );
            break;
        case DRAW_FILLING_FROM_DOWN:
            startInlineRectangle.x = startPoint.x + 1;
            startInlineRectangle.y = startPoint.y - 1 + (endPoint.y - startPoint.y) -
                                     draw_figure_generatePercentValue(
                                             maxScale,
                                             percentFilled,
                                             endPoint.y - startPoint.y - 2
                                     );

            endInlineRectangle.x = endPoint.x - 1;
            endInlineRectangle.y = endPoint.y - 1;
            break;
        default:;
    }
    draw_figure_rectangleFilled(startInlineRectangle, endInlineRectangle);
}