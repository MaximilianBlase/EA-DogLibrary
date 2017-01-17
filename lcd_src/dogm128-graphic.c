/*! @file dogm128-graphic.c
 *
 * @author Maximilian Blase
 * @date 2016-02-09
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

#include "dogm128-graphic.h"
#include <logging.h>

inline void dogmGraphic_setNewContent(uint8_t page) {
    dogmGraphic_newContent.value |= (1 << page);
}

void dogmGraphic_init(void) {
    // first complete clean
    dogmGraphic_clearWholeDisplay();

    dogmGraphic_writePointer.width = 2;
    dogmGraphic_writePointer.height.page = 7;
    dogmGraphic_writePointer.height.bit = 5;
    return;
}

void dogmGraphic_writeRamPage(uint8_t page) {
    DOGM_GOTO_ADDRESS(page, 0);
    for (uint8_t i = 0; i < DOGM_DISPLAY_WIDTH; i++) {
        dogm_data(display_content[page][i]);
    }
}

void dogmGraphic_flushRam(void* unused) {
    uint8_t pageMask = 0x01;
    for (uint8_t i = 0; i < 8; i++) {
        if (pageMask & dogmGraphic_newContent.value) {
            dogmGraphic_writeRamPage(i);
        }
        pageMask <<= 1;
    }

    //reset struct
    dogmGraphic_newContent.value = 0;
}

void dogmGraphic_setWritePointer(uint8_t width, uint8_t height) {
    if ((height < DOGM_DISPLAY_HEIGHT) && (width < DOGM_DISPLAY_WIDTH)) {
        dogmGraphic_writePointer.width = width;

        dogmGraphic_writePointer.height.page = height >> 3; //divide by 8
        dogmGraphic_writePointer.height.bit = height & 0x7;
    }
    else {
        logging_printString_P(LOG_WARNING, PSTR("Set write Pointer not possible; Out of range parameter"));
        return;
    }
}

inline uint8_t dogmGraphic_testWidth(uint8_t width) {
    return (width <= DOGM_DISPLAY_WIDTH) ? 1 : 0;
}

inline uint8_t dogmGraphic_testHeight(uint8_t height) {
    return (height <= DOGM_DISPLAY_HEIGHT) ? 1 : 0;
}

inline uint8_t dogmGraphic_testHeightPage(uint8_t page, uint8_t bit) {
    return (page < DOGM_DISPLAY_PAGES) && (bit < 8) ? 1 : 0;
}

void dogmGraphic_clearWholeDisplay(void) {
    for (uint8_t page = 0; page < DOGM_DISPLAY_PAGES; page++) {
        for (uint8_t col = 0; col < DOGM_DISPLAY_WIDTH; col++) {
            display_content[page][col] = 0x00;
        }
    }
    dogmGraphic_newContent.value = 0xff;
}

uint8_t dogmGraphic_generateByte(uint8_t number, uint8_t leftHand) {
    static const uint8_t byte = 8;
    return number > byte ? 0 : leftHand ? (uint8_t) (0xff >> (byte - number)) : ~((uint8_t) (0xff >> number));
}

void dogmGraphic_setVerticalPattern(uint8_t *verticalPattern, uint8_t startVertical, uint8_t deltaHeight) {
    for (uint8_t page = 0; page < DOGM_DISPLAY_PAGES; page++) {
        if ((startVertical >> 3) == ((startVertical + deltaHeight) >> 3)) {
            // startPage and endPage are the same
            verticalPattern[page] = 0xff;
            verticalPattern[page] <<= (startVertical & 0x07); // Modulo 8
            verticalPattern[page] &= dogmGraphic_generateByte((startVertical + deltaHeight) & 0x07, 1); // Modulo 8
        }
        else if (page < (startVertical >> 3)) { // divide by 8
            // position lower then start
            verticalPattern[page] = 0;
        }
        else if (page > ((startVertical + deltaHeight) >> 3)) { // divide by 8
            // position higher then end
            verticalPattern[page] = 0;
        }
        else if (page == (startVertical >> 3)) { // divide by 8
            // first position
            verticalPattern[page] = ~dogmGraphic_generateByte(startVertical & 0x07, 1); // Modulo 8
        }
        else if ((page != (((startVertical + deltaHeight) >> 3))) && (deltaHeight > 8)) { // divide by 8
            // middle position
            verticalPattern[page] = 0xff;
        }
        else {
            // last position
            verticalPattern[page] = dogmGraphic_generateByte((startVertical + deltaHeight) & 0x07, 1); // Modulo 8
        }
    }
}

void dogmGraphic_drawArea(uint8_t start_x, uint8_t start_y, uint8_t deltaWidth, uint8_t deltaHeight,
                          dogmGraphic_drawType_t type) {
    if (!dogmGraphic_testHeight(start_y) || !dogmGraphic_testWidth(start_x)) {
        logging_printString_P(LOG_WARNING, PSTR("Draw Area; StartPos out of range"));
        return;
    }
    uint8_t max_height = ((start_y + deltaHeight) >= DOGM_DISPLAY_HEIGHT) ? DOGM_DISPLAY_HEIGHT - 1 : (start_y +
                                                                                                       deltaHeight);
    uint8_t max_width = ((start_x + deltaWidth) >= DOGM_DISPLAY_WIDTH) ? DOGM_DISPLAY_WIDTH : (start_x + deltaWidth);

    uint8_t vertical_pattern[DOGM_DISPLAY_PAGES];
    dogmGraphic_setVerticalPattern(vertical_pattern, start_y, deltaHeight);

    dogmGraphic_setWritePointer(start_x, start_y);
    for (; dogmGraphic_writePointer.height.page <= (max_height >> 3); dogmGraphic_writePointer.height.page++) {
        for (dogmGraphic_writePointer.width = start_x;
             dogmGraphic_writePointer.width < max_width; dogmGraphic_writePointer.width++) {

            switch (type) {
                case DOGM_ADD:
                    display_content[dogmGraphic_writePointer.height.page][dogmGraphic_writePointer.width] |=
                            vertical_pattern[dogmGraphic_writePointer.height.page];
                    break;
                case DOGM_CLEAR:
                    display_content[dogmGraphic_writePointer.height.page][dogmGraphic_writePointer.width] &=
                            ~vertical_pattern[dogmGraphic_writePointer.height.page];
                    break;
                case DOGM_INVERT:
                    display_content[dogmGraphic_writePointer.height.page][dogmGraphic_writePointer.width] ^=
                            vertical_pattern[dogmGraphic_writePointer.height.page];
                    break;
                case DOGM_SET:
                    display_content[dogmGraphic_writePointer.height.page][dogmGraphic_writePointer.width] &=
                            ~vertical_pattern[dogmGraphic_writePointer.height.page];
                    display_content[dogmGraphic_writePointer.height.page][dogmGraphic_writePointer.width] |=
                            vertical_pattern[dogmGraphic_writePointer.height.page];
                    break;
                default:
                    logging_printString_P(LOG_WARNING, PSTR("Draw Area; DrawType unknown"));
            }
        }
        dogmGraphic_setNewContent(dogmGraphic_writePointer.height.page);
    }
}

void dogmGraphic_drawDot(uint8_t x, uint8_t y) {
    if (!dogmGraphic_testHeight(y) || !dogmGraphic_testWidth(x)) {
        logging_printString_P(LOG_WARNING, PSTR("Draw Dot; StartPos out of range"));
        return;
    }
    dogmGraphic_setWritePointer(x, y);
    display_content[dogmGraphic_writePointer.height.page][x] |= (uint8_t) (1 << (y & 0x07));

    dogmGraphic_setNewContent(dogmGraphic_writePointer.height.page);
}

inline int8_t dogmGraphic_sgn(int8_t x) {
    return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}

void dogmGraphic_drawLineXY(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y, uint8_t lineType) {
    int8_t x, y, t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, es, el, err;

    /* Entfernung in beiden Dimensionen berechnen */
    dx = end_x - start_x;
    dy = end_y - start_y;

    /* Vorzeichen des Inkrements bestimmen */
    incx = dogmGraphic_sgn(dx);
    incy = dogmGraphic_sgn(dy);
    if (dx < 0) { dx = -dx; }
    if (dy < 0) { dy = -dy; }

    /* feststellen, welche Entfernung größer ist */
    if (dx > dy) {
        /* x ist schnelle Richtung */
        pdx = incx;
        pdy = 0;    /* pd. ist Parallelschritt */
        ddx = incx;
        ddy = incy; /* dd. ist Diagonalschritt */
        es = dy;
        el = dx;   /* Fehlerschritte schnell, langsam */
    } else {
        /* y ist schnelle Richtung */
        pdx = 0;
        pdy = incy; /* pd. ist Parallelschritt */
        ddx = incx;
        ddy = incy; /* dd. ist Diagonalschritt */
        es = dx;
        el = dy;   /* Fehlerschritte schnell, langsam */
    }

    /* Initialisierungen vor Schleifenbeginn */
    x = start_x;
    y = start_y;
    err = el >> 1; // divide by 2
    dogmGraphic_drawDot((uint8_t) x, (uint8_t) y);

    /* Pixel berechnen */
    for (t = 0; t < el; ++t) /* t zaehlt die Pixel, el ist auch Anzahl */
    {
        /* Aktualisierung Fehlerterm */
        err -= es;
        if (err < 0) {
            /* Fehlerterm wieder positiv (>=0) machen */
            err += el;
            /* Schritt in langsame Richtung, Diagonalschritt */
            x += ddx;
            y += ddy;
        } else {
            /* Schritt in schnelle Richtung, Parallelschritt */
            x += pdx;
            y += pdy;
        }

        switch (lineType) {
            case 0: // filled
                dogmGraphic_drawDot((uint8_t) x, (uint8_t) y);
                break;
            case 1: // dotted
                if (t & 0x01) {
                    dogmGraphic_drawDot((uint8_t) x, (uint8_t) y);
                }
                break;
            case 2: // dashed
                if ((t & 0x02)) {
                    dogmGraphic_drawDot((uint8_t) x, (uint8_t) y);
                }
                break;
            default:
                logging_printString_P(LOG_WARNING, PSTR("Draw Line; LineType unknown"));
        }
    }
}

void dogmGraphic_drawCircleOutline(uint8_t start_x, uint8_t start_y, uint8_t radius, uint8_t filled) {
    int8_t f = 1 - radius;
    int8_t ddF_x = 0;
    int8_t ddF_y = 1 - (radius << 1); // Multiply by -2
    int8_t x = 0;
    int8_t y = radius;

    dogmGraphic_drawDot(start_x, start_y + radius);
    dogmGraphic_drawDot(start_x, start_y - radius);
    dogmGraphic_drawDot(start_x + radius, start_y);
    dogmGraphic_drawDot(start_x - radius, start_y);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;

        if (filled) {
            //first line
            dogmGraphic_drawLineXY(start_x, start_y - y, start_x, start_y + y, 0);
            //middle
            dogmGraphic_drawLineXY(start_x + x, start_y - y, start_x + x, start_y + y, 0);
            dogmGraphic_drawLineXY(start_x - x, start_y + y, start_x - x, start_y - y, 0);
            //end
            dogmGraphic_drawLineXY(start_x + y, start_y - x, start_x + y, start_y + x, 0);
            dogmGraphic_drawLineXY(start_x - y, start_y + x, start_x - y, start_y - x, 0);
        }
        else {
            dogmGraphic_drawDot(start_x + x, start_y + y);
            dogmGraphic_drawDot(start_x - x, start_y + y);

            dogmGraphic_drawDot(start_x + x, start_y - y);
            dogmGraphic_drawDot(start_x - x, start_y - y);

            dogmGraphic_drawDot(start_x + y, start_y + x);
            dogmGraphic_drawDot(start_x - y, start_y + x);

            dogmGraphic_drawDot(start_x + y, start_y - x);
            dogmGraphic_drawDot(start_x - y, start_y - x);
        }
    }
}

void dogmGraphic_drawP(uint8_t start_x, uint8_t start_y, uint8_t deltaWidth, uint8_t deltaHeight,
                       dogmGraphic_drawType_t type, const void *progMemSpace) {
    // proof of start point and size
    if (
            !dogmGraphic_testHeight(start_y) ||
            !dogmGraphic_testWidth(start_x) ||
            !dogmGraphic_testHeight(start_y + deltaHeight) ||
            !dogmGraphic_testWidth(start_x + deltaWidth)
        ) {
        logging_printString_P(LOG_WARNING, PSTR("Draw PROGMEM; Position out of range"));
        return;
    }

    uint8_t verticalPattern[DOGM_DISPLAY_PAGES];
    dogmGraphic_setWritePointer(start_x, start_y);
    dogmGraphic_setVerticalPattern(verticalPattern, start_y, deltaHeight);

    // area for loop in pages
    dogmGraphic_setWritePointer(start_x, start_y);
    for (; dogmGraphic_writePointer.height.page <= ((start_y + deltaHeight) >> 3);
           dogmGraphic_writePointer.height.page++) {
        uint8_t page = dogmGraphic_writePointer.height.page;

        //TODO: On occasion find the real problem
        if (page >= (DOGM_DISPLAY_HEIGHT >> 3)) { // divide by 8
            logging_printString_P(LOG_WARNING, PSTR("Draw PROGMEM; Page on 8 or higher"));
            break;
        }
        for (uint8_t i = start_x; i < (start_x + deltaWidth); i++) {

            uint8_t writeContent = 0;
            if ((start_y >> 3) == ((start_y + deltaHeight) >> 3)) { // divide by 8
                // start page == end page
                writeContent = ((pgm_read_byte(progMemSpace)) << dogmGraphic_writePointer.height.bit);
                writeContent &= dogmGraphic_generateByte(dogmGraphic_writePointer.height.bit + deltaHeight, 1);
            }
            else if (page == (start_y >> 3)) { // divide by 8
                // start page
                writeContent = ((pgm_read_byte(progMemSpace)) << dogmGraphic_writePointer.height.bit);
            }
            else if (page < ((start_y + deltaHeight) >> 3)) { // divide by 8
                // between start and end page
                writeContent = ((pgm_read_byte(progMemSpace - deltaWidth)) >>
                                (8 - dogmGraphic_writePointer.height.bit));
                writeContent |= ((pgm_read_byte(progMemSpace)) << dogmGraphic_writePointer.height.bit);
            }
            else {
                writeContent = ((pgm_read_byte(progMemSpace - deltaWidth)) >>
                                (8 - dogmGraphic_writePointer.height.bit));
            }

            switch (type) {
                case DOGM_ADD:
                    display_content[page][i] |= (writeContent & verticalPattern[page]);
                    break;
                case DOGM_CLEAR: // not needed in this case
                    break;
                case DOGM_INVERT:
                    display_content[page][i] &= ~verticalPattern[page];
                    writeContent ^= verticalPattern[page];
                    display_content[page][i] |= writeContent;
                    break;
                case DOGM_SET:
                    display_content[page][i] &= ~verticalPattern[page];
                    display_content[page][i] |= (writeContent & verticalPattern[page]);
                    break;
                default:
                    logging_printString_P(LOG_WARNING, PSTR("Draw PROGMEM; DrawType unknown"));
            }
            progMemSpace++;
        }
        dogmGraphic_setNewContent(page);
    }
}