/*! @file dogm128.h
 *
 * @author Jan Wiese
 * @date 2016-02-15
 *
 *
 * #####################################################################################################################
 * @Copyright (c) 2016, J.Wiese, <jw-lighting at ewetel dot net>
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

#ifndef MCU_DOGM128_H
#define MCU_DOGM128_H

#include <stdint.h>
#include "../sys_src/iodef.h"

//Display dimension
#define DOGM_DISPLAY_HEIGHT     64
#define DOGM_DISPLAY_WIDTH      128
#define DOGM_DISPLAY_PAGES      DOGM_DISPLAY_HEIGHT/8

void dogm_init(void);

void dogm_data(uint8_t data);

void dogm_cmd(uint8_t cmd);

void dogm_send(uint8_t byte);

void dogm_init_spi(void);

// Settings

#define DOGM_IS_TOPVIEW         1
#define DOGM_CONTRAST           0x04

// Abbreviations (macros)

#define DOGM_SET_DDR()          DISPDDR |= (1<<DISPCS)|(1<<DISPRESET)|(1<<DISPA0)
#define DOGM_INIT_SPI()         SPCR = (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (1 << CPHA);\
                                SPSR = (1 << SPI2X);
#define DOGM_SELECT()           DISPPORT &= ~(1<<DISPCS)
#define DOGM_UNSELECT()         DISPPORT |= (1<<DISPCS)
#define DOGM_COMMAND()          DISPPORT &= ~(1<<DISPA0)
#define DOGM_DATA()             DISPPORT |= (1<<DISPA0)
#define DOGM_RESET()            DISPPORT &= ~(1<<DISPRESET)
#define DOGM_RUN()              DISPPORT |= (1<<DISPRESET); SPSR |= (1 << SPIF)

#define DOGM_SPIDR              SPDR
#define DOGM_BUSY_WAITING()     while(!(SPSR & (1<<SPIF)));

// Commands

#define DOGM_DISPLAY_ENABLE             0xAE
#define DOGM_START_LINE                 0x40
#define DOGM_PAGE_ADDRESS               0xB0
#define DOGM_COL_ADDRESS                0x10
#define DOGM_BOTTOMVIEW                 0xA0
#define DOGM_DISPLAY_INVERT             0xA6
#define DOGM_ALL_PIXEL                  0xA4
#define DOGM_BIAS                       0xA2
#define DOGM_RST_CMD                    0xE2
#define DOGM_SCAN_DIR                   0xC0
#define DOGM_POWER_CONTROL              0x28
#define DOGM_VOLTAGE                    0x20
#define DOGM_VOLUME_MODE                0x81
#define DOGM_NOP_CMD                    0xE3
#define DOGM_INDICATOR                  0xAC
#define DOGM_BOOSTER_SET                0xF8

#if DOGM_IS_TOPVIEW
#define DOGM_COLUMN_ADD                 4
#else
#define DOGM_COLUMN_ADD                 0
#endif

#define DOGM_ON()                       dogm_cmd(DOGM_DISPLAY_ENABLE | 1)
#define DOGM_OFF()                      dogm_cmd(DOGM_DISPLAY_ENABLE | 0)
#define DOGM_USE_FIRST_LINE(i)          dogm_cmd(DOGM_START_LINE | ((i) & 0x3F))
#define DOGM_GOTO_PAGE_ADDR(i)          dogm_cmd(DOGM_PAGE_ADDRESS | ((i) & 0x0F))
#define DOGM_GOTO_COLUMN_ADDR(col)      dogm_cmd(DOGM_COL_ADDRESS | ((((col)+DOGM_COLUMN_ADD)>>4) & 0x0F)); \
                                        dogm_cmd((((col)+DOGM_COLUMN_ADD) & 0x0F))
#define DOGM_GOTO_ADDRESS(page, col)    DOGM_GOTO_PAGE_ADDR(page); \
                                        DOGM_GOTO_COLUMN_ADDR(col)
#define DOGM_USE_BOTTOM_VIEW()          dogm_cmd(DOGM_BOTTOMVIEW | 1)
#define DOGM_USE_TOP_VIEW()             dogm_cmd(DOGM_BOTTOMVIEW | 0)
#define DOGM_USE_MODE_POSITIVE()        dogm_cmd(DOGM_DISPLAY_INVERT | 0)
#define DOGM_USE_MODE_INVERTED()        dogm_cmd(DOGM_DISPLAY_INVERT | 1)
#define DOGM_ALL_PIXELS_ON()            dogm_cmd(DOGM_ALL_PIXEL | 1)
#define DOGM_ALL_PIXELS_OFF()           dogm_cmd(DOGM_ALL_PIXEL | 0)
#define DOGM_USE_BIAS_RATIO_1_7()       dogm_cmd(DOGM_BIAS | 1)
#define DOGM_USE_BIAS_RATIO_1_9()       dogm_cmd(DOGM_BIAS | 0)
#define DOGM_SOFTRESET()                dogm_cmd(DOGM_RST_CMD)
#define DOGM_SCAN_NORMAL()              dogm_cmd(DOGM_SCAN_DIR | 0x0)
#define DOGM_SCAN_UPSIDEDOWN()          dogm_cmd(DOGM_SCAN_DIR | 0x8)
#define DOGM_USE_POWER_CONTROL(i)       dogm_cmd(DOGM_POWER_CONTROL | ((i) & 0x07))
#define DOGM_USE_LOW_POWER()            dogm_cmd(DOGM_POWER_CONTROL | 0x7)
#define DOGM_USE_LOW_VOLTAGE()          dogm_cmd(DOGM_POWER_CONTROL | 0x3)
#define DOGM_USE_BIAS_VOLTAGE(i)        dogm_cmd(DOGM_VOLTAGE | ((i) & 0x07))
#define DOGM_USE_VOLUME_MODE(i)         dogm_cmd(DOGM_VOLUME_MODE); dogm_cmd(((i) & 0x3F))
#define DOGM_NOP()                      dogm_cmd(DOGM_NOP_CMD)
#define DOGM_USE_INDICATOR_OFF()        dogm_cmd(DOGM_INDICATOR | 0); dogm_cmd(0x00)
#define DOGM_USE_INDICATOR_STATIC()     dogm_cmd(DOGM_INDICATOR | 1); dogm_cmd(0x11)
#define DOGM_USE_INDICATOR_1HZ()        dogm_cmd(DOGM_INDICATOR | 1); dogm_cmd(0x01)
#define DOGM_USE_INDICATOR_2HZ()        dogm_cmd(DOGM_INDICATOR | 1); dogm_cmd(0x10)
#define DOGM_USE_INDICATOR(i, j)        dogm_cmd(DOGM_INDICATOR | ((i) & 1)); dogm_cmd(((j) & 2))
#define DOGM_USE_BOOSTER_MODE(i)        dogm_cmd(DOGM_BOOSTER_SET); dogm_cmd(((i) & 0x03))
#define DOGM_USE_BOOSTER_MODE_234       dogm_cmd(DOGM_BOOSTER_SET); dogm_cmd(0x0)
#define DOGM_USE_BOOSTER_MODE_5         dogm_cmd(DOGM_BOOSTER_SET); dogm_cmd(0x1)
#define DOGM_USE_BOOSTER_MODE_6         dogm_cmd(DOGM_BOOSTER_SET); dogm_cmd(0x3)
#define DOGM_SLEEP_MODE                 dogm_cmd(DOGM_INDICATOR_OFF);\
                                        dogm_cmd(DOGM_DISPLAY_ENABLE | 0);\
                                        dogm_cmd(DOGM_ALL_PIXEL | 1)

#endif //MCU_DOGM128_H