//
// Created by jawiese on 15.02.16.
//

#ifndef MCU_RINGBUF_H
#define MCU_RINGBUF_H

#define BUFFER_SIZE     512

typedef struct {
    char content[BUFFER_SIZE];
    char *writePtr;
    volatile char *readPtr;
} ringBuffer_t;

void bufferInit(ringBuffer_t *buffer);

char bufferRead(ringBuffer_t *buffer);

void bufferWrite(ringBuffer_t *buffer, char val);

void bufferClear(ringBuffer_t *buffer);

#endif //MCU_RINGBUF_H
