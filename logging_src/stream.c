/*
 * author: Maximilian Blase
 * date:   06.07.16
 */

#include "stream.h"
#include "uart.h"

static int uart_putCharStream(char c, FILE* stream);

static FILE stdUART = FDEV_SETUP_STREAM(uart_putCharStream, NULL, _FDEV_SETUP_WRITE);

static int uart_putCharStream(char c, FILE* stream) {
    if (c == '\n') {
        uart_putCharStream('\r', stream);
    }

    uart_putChar(UART_DEBUG, c);
    return 0;
}

void stream_init(void) {
    uart_init(UART_DEBUG);

    stdin = &stdUART;
    stdout = &stdUART;
    stderr = &stdUART;
}
