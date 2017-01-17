/*
 * author: Maximilian Blase
 * date:   06.07.16
 */

#ifndef MCU_LOGGING_H
#define MCU_LOGGING_H

#include <avr/io.h>

typedef enum {
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL_ERROR
}logLevel_t;

logLevel_t logLevelIntern;

void logging_init(logLevel_t logLevel);

void logging_setLogLevel(logLevel_t logLevel);

void logging_printString(logLevel_t logLevel, char* string);

void logging_printString_P(logLevel_t logLevel, const char* string);

void logging_printStringFileLine(logLevel_t logLevel, char* string, char* file, int line);

void logging_printPartlyStringStart(logLevel_t logLevel, char* string);

void logging_printPartlyStringAppend(logLevel_t logLevel, char* string);

void logging_printPartlyStringAppend_P(logLevel_t logLevel, const char* string);

void logging_printPartlyNumberUint16Append(logLevel_t logLevel, uint16_t number, uint8_t base);

void logging_printPartlyStringEnd(logLevel_t logLevel);

const char* logging_getLogLevelName(void);

#endif //MCU_LOGGING_H
