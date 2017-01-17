/*
 * author: Maximilian Blase
 * date:   06.07.16
 */

#ifndef MCU_UART_H
#define MCU_UART_H

#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum {
    UART_USB = 0,
    UART_DEBUG = 1
}UART_CHOICE_t;

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
