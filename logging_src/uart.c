/*! @file uart.c
 *
 * @author Maximilian Blase
 * @date 2016-07-06
 *
 * #####################################################################################################################
 * @Copyright (c) 2017, M.Blase, info@maximilian-blase.de
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

#include <stdlib.h>
#include "uart.h"
#include "ringbuf.h"

ringBuffer_t uartBuffer[2];

void uart_startString(UART_CHOICE_t uart);

void uart_init(UART_CHOICE_t uart) {
    switch (uart) {
        default:
        case UART_USB:
            UART_UCSRA0 = (UART_U2X_SET << U2X0);
            UART_UCSRB0 = (1 << TXEN0) | (1 << TXCIE0); // enable transmitter and data register empty ISR
            UART_UCSRC0 = (1 << UCSZ01) | (1 << UCSZ00); // use 8 data bits, no parity, 1 stop bit
            UART_UBRR0 = UART_UBRR_VAL;
            UART_TXDDRSET0;

            bufferInit(&uartBuffer[UART_USB]);
            uart_startString(UART_USB);
            break;
        case UART_DEBUG:
            UART_UCSRA1 = (UART_U2X_SET << U2X0);
            UART_UCSRB1 = (1 << TXEN0) | (1 << TXCIE0); // enable transmitter and data register empty ISR
            UART_UCSRC1 = (1 << UCSZ01) | (1 << UCSZ00); // use 8 data bits, no parity, 1 stop bit
            UART_UBRR1 = UART_UBRR_VAL;
            UART_TXDDRSET1;

            bufferInit(&uartBuffer[UART_DEBUG]);
            uart_startString(UART_DEBUG);
            break;
    }
}

void uart_putChar(UART_CHOICE_t uart, char c) {
    switch (uart) {
        default:
        case UART_USB:
            bufferWrite(&uartBuffer[UART_USB], c);

            if (*uartBuffer[UART_USB].readPtr == c) {
                //start uart
                loop_until_bit_is_set(UART_UCSRA0, UART_UDRE0);
                char content = bufferRead(&uartBuffer[UART_USB]);
                if (content) {
                    UART_UDR0 = (uint8_t) c;
                }
            }
            break;
        case UART_DEBUG:
            bufferWrite(&uartBuffer[UART_DEBUG], c);

            if (*uartBuffer[UART_DEBUG].readPtr == c) {
                //start uart
                loop_until_bit_is_set(UART_UCSRA1, UART_UDRE1);
                char content = bufferRead(&uartBuffer[UART_DEBUG]);
                if (content) {
                    UART_UDR1 = (uint8_t) c;
                }
            }
            break;
    }
}

void uart_putString(UART_CHOICE_t uart, char* string) {

    while (*string) {
        uart_putChar(uart, *string);
        string++;
    }
}

void uart_putNumberUint16_t(UART_CHOICE_t uart, uint16_t number, uint8_t base) {
    char numberStr[7];
    utoa(number, numberStr, base);

    uart_putString(uart, numberStr);
}

void uart_putNumberUint32_t(UART_CHOICE_t uart, uint32_t number, uint8_t base) {
    char numberStr[12];
    ultoa(number, numberStr, base);

    uart_putString(uart, numberStr);
}

void uart_putNumberInt16_t(UART_CHOICE_t uart, int16_t number, uint8_t base) {
    char numberStr[7];
    itoa(number, numberStr, base);

    uart_putString(uart, numberStr);
}

void uart_putNumberInt32_t(UART_CHOICE_t uart, int32_t number, uint8_t base) {
    char numberStr[12];
    ltoa(number, numberStr, base);

    uart_putString(uart, numberStr);
}

inline void uart_startString(UART_CHOICE_t uart) {
    char* string = "\nUART gestartet:\n";

    while (*string) {
        uart_putChar(uart, *string);
        string++;
    }
}

ISR(UART_TX_ISR0) {
    char c = bufferRead(&uartBuffer[UART_USB]);
    if (c != 0) {
        UART_UDR0 = (uint8_t) c;
    }
}

ISR(UART_TX_ISR1) {
    char c = bufferRead(&uartBuffer[UART_DEBUG]);
    if (c != 0) {
        UART_UDR1 = (uint8_t) c;
    }
}