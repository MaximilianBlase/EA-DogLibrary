/*
 * author: Maximilian Blase
 * date: 2017 01 17
 */

//AVR includes

//OWN includes
#include "../lcd_src/dogm128.h"
#include "../lcd_src/dogm128-graphic.h"
#include "../lcd_src/drawing/drawingInclude.h"
#include "../logging_src/logging.h"

int main(void) {
    logging_init(LOG_INFO);

    dogm_init();
    dogmGraphic_init();
    draw_font_setCursorXY(0, 0);
    draw_font_setCursorLineEnd(DOGM_DISPLAY_WIDTH - 1);
    draw_font_setFont(FONT_PROP_8);

    logging_printString_P(LOG_INFO, PSTR("Init done"));
    while (1) {

    }
}