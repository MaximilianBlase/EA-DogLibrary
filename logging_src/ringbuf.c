//
// Created by jawiese on 15.02.16.
//


#include "ringbuf.h"

void bufferInit(ringBuffer_t *buffer) {
    buffer->writePtr = buffer->content;
    buffer->readPtr = buffer->content;
}

char bufferRead(ringBuffer_t *buffer) {
    char c = *buffer->readPtr;
    if (c == 0) { // end of content
        return c;
    }
    *buffer->readPtr = 0; // delete
    buffer->readPtr++; // inc position
    if (buffer->readPtr >= (buffer->content + BUFFER_SIZE)) { // buffer end
        buffer->readPtr = buffer->content; // rewind
    }
    return c;
}

void bufferWrite(ringBuffer_t *buffer, char val) {
    *buffer->writePtr = val; // write
    buffer->writePtr++; // inc position
    if (buffer->writePtr >= (buffer->content + BUFFER_SIZE)) {  // buffer end
        buffer->writePtr = buffer->content; // rewind
    }
}

void bufferClear(ringBuffer_t *buffer) {
    for (char *i = buffer->content; i < (buffer->content + BUFFER_SIZE); i++) {
        *i = 0;
    }
    buffer->writePtr = buffer->content;
    buffer->readPtr = buffer->content;
}


