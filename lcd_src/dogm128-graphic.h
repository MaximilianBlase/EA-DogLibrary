/*! @file dogm128-graphic.h
 *
 * @author Maximilian Blase
 * @date 2016-02-09
 *
 * @date 2016-02-24
 * @note This file contains the graphic functions laying on the deepest layer. This file implements a ram copy of the
 * actual screen, changes pixel on it and flashes them to the hardware display. So this functions transform the x/y
 * coordinate system based on the higher layer to the real byte representation in vertical direction for the display.
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

#ifndef MCU_DOGM_GRAPHIC_H
#define MCU_DOGM_GRAPHIC_H

#include <stdint.h>
#include <avr/pgmspace.h>

#include "dogm128.h"

/*! @brief actual display copy in ram
 *
 * This array represents a copy of the actual showed display. Every function will only change bits in this area and
 * set bits in another array, so that the changed pages can be actualised on the display. The width is represented in
 * pixel, so that one width byte only represent one horizontal pixel in real. The vertical direction is divided in
 * bytes, so that for example a height of 64 pixel is stored in 8 bytes, because every byte represents in vertical
 * direction 8 pixel. Therefore it is necessary to implement a transformation between width[px]/height[pages] to x/y.
 * This transformation will be done on the higher layers.
 */
uint8_t display_content[DOGM_DISPLAY_PAGES][DOGM_DISPLAY_WIDTH];

/*! @brief information about needed refresh pages
 *
 * This union contains information about vertical pages, that need to be refreshed. Every function will set the correct
 * bits in this union to tell the graphic hardware part, that the display is outdated on that places. For a better set-
 * ting solution, it is easy possible to set the whole display at once, or to tell every bit on its own, that it needs
 * to be refreshed.
 */
typedef union {
    uint8_t value;
    struct {
        unsigned page0:1;
        unsigned page1:1;
        unsigned page2:1;
        unsigned page3:1;
        unsigned page4:1;
        unsigned page5:1;
        unsigned page6:1;
        unsigned page7:1;
    } pages;
} newContent_t;

newContent_t dogmGraphic_newContent;

/*! @brief set newContent flags
 *
 * @param page      new content in this page
 *
 * This internal functions sets the specific bit with the given number in the newContent struct.
 */
void dogmGraphic_setNewContent(uint8_t page);

/*! @brief actual low level cursor in ram
 *
 * This struct represents on a very low layer the actual position on the ram copy. With this struct it is a little bit
 * more easy to iterate about the horizontal or the vertical position in bytes. Also it is possible to get the actual
 * vertical bit position in the vertical page.
 */
struct {
    struct {
        uint8_t page;
        uint8_t bit;
    } height;
    uint8_t width;
} dogmGraphic_writePointer;

/*******************************************************************************
 * init
 ******************************************************************************/

/*! @brief graphic init
 *
 * This function initialise the ram copy and clears it. It is very imported, that this function is used at first in the
 * beginning of the main function. This function should only be used once.
 */
void dogmGraphic_init(void);

/*! @brief write given page to display
 *
 * @param page  vertical page to update
 *
 * This function actualise the given vertical page on the display with the data of the ram copy.
 */
void dogmGraphic_writeRamPage(uint8_t page);

/*! @brief actualize display content
 *
 * This function actualise all vertical pages on the display given with the newContent struct. After all, the bits
 * in the parameter will be set to zero.
 */
void dogmGraphic_flushRam(void* unused);

/*! @brief
 *
 * @param width     horizontal pos
 * @param height    vertical pos
 *
 * This function transforms the given coordinates of an x/y coordinate system into the deep page system for the display.
 * The height will be splitted in page and bit and the cursor will also be set width this coordinates.
 */
void dogmGraphic_setWritePointer(uint8_t width, uint8_t height);

/*******************************************************************************
 * valid tests
 ******************************************************************************/

/*! @brief test horizontal position
 *
 * @param width     horizontal position
 *
 * This inline functions returns true, if the given horizontal position is inside the display area. The horizontal
 * position is given in the x/y coordinate system.
 */
uint8_t dogmGraphic_testWidth(uint8_t width);

/*! @brief test vertical position
 *
 * @param height    vertical position
 *
 * This inline function returns true, if the given vertical position is inside the display area. The vertical position
 * is given in the x/y coordinate system.
 */
uint8_t dogmGraphic_testHeight(uint8_t height);

/*! @brief test vertical position
 *
 * @param page      vertical position in complete pages
 * @param bit       vertical position in page
 *
 * This inline function returns true, if the given vertical position is inside the display area. The vertical position
 * is given in the page coordinate system.
 */
uint8_t dogmGraphic_testHeightPage(uint8_t page, uint8_t bit);

/*******************************************************************************
 * clear display
 ******************************************************************************/

/*! @brief clear complete display
 *
 * This function sets the complete ram copy to zero. Very effective.
 */
void dogmGraphic_clearWholeDisplay(void);

/*! @brief generate specific byte
 *
 * @param number    number of bit to set in byte
 * @param leftHand  1=set bits from left, 0=set bits from right
 *
 * @return          byte with set bits inside
 *
 * This function returns Byte with specific bits set inside. The given number represents the count of set bits. This
 * parameter leftHand detects, if the bits are set from left side, or from right side.
 *
 * Example:
 * number=3 leftHand=1      return = 1110 0000
 * number=3 leftHand=0      return = 0000 0111
 * number=5 leftHand=1      return = 1111 1000
 */
uint8_t dogmGraphic_generateByte(uint8_t number, uint8_t leftHand);

/*******************************************************************************
 * draw dots, lines and figures
 ******************************************************************************/

/*! @brief specify types of drawing
 *
 * @param DOGM_ADD      add the given pixel
 * @param DOGM_CLEAR    clear the given pixel
 * @param DOGM_INVERT   invert the given pixel
 * @param DOGM_SET      set the given pixel
 *
 * This enum represents different types of drawing data.
 */
typedef enum drawType {
    DOGM_ADD = 0, DOGM_CLEAR, DOGM_INVERT, DOGM_SET
} dogmGraphic_drawType_t;

/*! @brief generate vertical line
 *
 * @param verticalPattern   empty uint8_t array of page length
 * @param startVertical     vertical start position in px
 * @param deltaHeight       number of bits to set in pattern
 *
 * This function sets a number of bits in the given array specified with deltaHeight. The bits start at the given start
 * position. This function can be used to get a vertical line of the complete display height to detect, where bits
 * should be changed.
 */
void dogmGraphic_setVerticalPattern(uint8_t *verticalPattern, uint8_t startVertical, uint8_t deltaHeight);

/*! @brief draw a rectangle area on screen
 *
 * @param start_x       start position in horizontal direction at top left in x/y coordinate system
 * @param start_y       start position in vertical direction at top left in x/y coordinate system
 * @param deltaWidth    width of the drawn rectangle
 * @param deltaHeight   height of the drawn rectangle
 * @param type          type to draw pixel
 *
 * This generic function sets a number of pixel on the screen specified with the given type. The rectangle area starts
 * with the given coordinate values in x/y coordinate system on the top left corner.
 */
void dogmGraphic_drawArea(uint8_t start_x, uint8_t start_y, uint8_t deltaWidth, uint8_t deltaHeight,
                          dogmGraphic_drawType_t type);

/*! @brief set one pixel
 *
 * @param x     horizontal position
 * @param y     vertical position
 *
 * This function sets one pixel in the x/y coordinate system. This function is often used in abstract figure functions.
 */
void dogmGraphic_drawDot(uint8_t x, uint8_t y);

/*! @brief signum function
 *
 * @param x     signed value
 *
 * @return      corrected value
 *
 * @see https://de.wikipedia.org/wiki/Bresenham-Algorithmus
 */
int8_t dogmGraphic_sgn(int8_t x);

/*! @brief Bresenham-Algorithmus Linie
 *
 * @param start_x   horizontal start position
 * @param start_y   vertical start position
 * @param end_x     horizontal end position
 * @param end_y     vertical end position
 * @param lineType  0=filled, 1=dotted, 2=dashed
 *
 * @see https://de.wikipedia.org/wiki/Bresenham-Algorithmus
 */
void dogmGraphic_drawLineXY(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y, uint8_t lineType);

/*! @brief Bresenham-Algorithmus Kreis
 *
 * @param start_x   horizontal start position
 * @param start_y   vertical start position
 * @param radius    half diameter of the circle
 * @param filled    1= completely fill circle; 0= only outline circle
 *
 * @see https://de.wikipedia.org/wiki/Bresenham-Algorithmus
 */
void dogmGraphic_drawCircleOutline(uint8_t start_x, uint8_t start_y, uint8_t radius, uint8_t filled);

/*******************************************************************************
 * draw PROGMEM pics
 ******************************************************************************/

/*! @brief draw data from flash on screen
 *
 * @param start_x       horizontal start position on top left corner
 * @param start_y       vertical start position on top left corner
 * @param deltaWidth    width in pixel of data
 * @param deltaHeight   height in pixel of data
 * @param type          type to draw pixel
 * @param progMemSpace  start byte of data in flash
 *
 * This function draws data from flash to screen in the specific area.
 */
void dogmGraphic_drawP(uint8_t start_x, uint8_t start_y, uint8_t deltaWidth, uint8_t deltaHeight,
                       dogmGraphic_drawType_t type, const void *progMemSpace);

#endif //MCU_DOGM_GRAPHIC_H