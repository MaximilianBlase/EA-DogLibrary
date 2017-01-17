/*! @file uart.h
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

#ifndef MCU_UART_H
#define MCU_UART_H

#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum {
    UART_USB = 0,
    UART_DEBUG = 1
} UART_CHOICE_t;

#define UART_UBRR_VAL   16 // 115200bd @ 16MHz
#define UART_U2X_SET    1

// UART_USB
#define UART_UDR0       UDR0
#define UART_UCSRA0     UCSR0A
#define UART_UCSRB0     UCSR0B
#define UART_UCSRC0     UCSR0C
#define UART_UBRR0      UBRR0
#define UART_UDRE0      UDRE0
#define UART_UDRE_ISR0  USART0_UDRE_vect
#define UART_TX_ISR0    USART0_TX_vect
#define UART_TXDDRSET0  DDRD |= (1 << PD1)

// UART_DEBUG
#define UART_UDR1       UDR1
#define UART_UCSRA1     UCSR1A
#define UART_UCSRB1     UCSR1B
#define UART_UCSRC1     UCSR1C
#define UART_UBRR1      UBRR1
#define UART_UDRE1      UDRE1
#define UART_UDRE_ISR1  USART1_UDRE_vect
#define UART_TX_ISR1    USART1_TX_vect
#define UART_TXDDRSET1  DDRD |= (1 << PD3)

void uart_init(UART_CHOICE_t uart);

void uart_putChar(UART_CHOICE_t uart, char c);

void uart_putString(UART_CHOICE_t uart, char* string);

void uart_putNumberUint16_t(UART_CHOICE_t uart, uint16_t number, uint8_t base);

void uart_putNumberUint32_t(UART_CHOICE_t uart, uint32_t number, uint8_t base);

void uart_putNumberInt16_t(UART_CHOICE_t uart, int16_t number, uint8_t base);

void uart_putNumberInt32_t(UART_CHOICE_t uart, int32_t number, uint8_t base);

#endif //MCU_UART_H
