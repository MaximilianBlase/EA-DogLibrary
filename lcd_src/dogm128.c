/*! @file dogm128.c
 *
 * @author Jan Wiese
 * @date 2016-02-15
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

#include <util/delay.h>
#include <avr/interrupt.h>
#include "dogm128.h"

void dogm_init(void) {
    DOGM_SET_DDR();
    dogm_init_spi();

    DOGM_RESET();
    _delay_ms(1);
    DOGM_RUN();

    DOGM_USE_FIRST_LINE(0);
#ifdef DOGM_IS_TOPVIEW
    DOGM_USE_TOP_VIEW();
    DOGM_SCAN_UPSIDEDOWN();
#else
    DOGM_USE_BOTTOM_VIEW();
    DOGM_SCAN_NORMAL();
#endif

    DOGM_ALL_PIXELS_OFF();
    DOGM_USE_MODE_POSITIVE();
    DOGM_USE_BIAS_RATIO_1_7();
    DOGM_USE_LOW_POWER();
    DOGM_USE_BIAS_VOLTAGE(0x07);
    DOGM_USE_VOLUME_MODE(DOGM_CONTRAST);
    DOGM_USE_INDICATOR_OFF();

    DOGM_ON();

    DOGM_GOTO_ADDRESS(0, 0);
}


void dogm_data(uint8_t data) {
    DOGM_DATA();
    dogm_send(data);
}

void dogm_cmd(uint8_t cmd) {
    DOGM_COMMAND();
    dogm_send(cmd);
}

inline void dogm_send(uint8_t byte) {
    ///TODO: backup is unneeded
    //uint8_t SPCRbak, SPSRbak;
    //SPCRbak = SPCR;
    //SPSRbak = SPSR;

    DOGM_INIT_SPI();

    DOGM_SELECT();
    DOGM_SPIDR = byte;
    DOGM_BUSY_WAITING();
    DOGM_UNSELECT();

    // tidy up
    //SPCR = SPCRbak;
    //SPSR = SPSRbak;
}

void dogm_init_spi(void) {
    DISPDDR |= (1 << DISPMOSI) | (1 << DISPSCK);
    DOGM_INIT_SPI();
    /*SPCR = (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (1 << CPHA);
    SPSR = (1 << SPI2X);
    SPDR = DOGM_NOP_CMD;*/
}

