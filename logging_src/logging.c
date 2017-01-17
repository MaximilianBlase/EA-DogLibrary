/*
 * author: Maximilian Blase
 * date:   06.07.16
 */

#include <avr/pgmspace.h>
#include <stdlib.h>

#include "logging.h"
#include "stream.h"

void printString(char* string, uint8_t errorStream);
void printString_P(const char* string, uint8_t errorStream);
void printNewLine(uint8_t errorStream);

void logging_init(logLevel_t logLevel) {
    stream_init();
#if (_DEBUG_MODE)
    printString("Logging gestartet: mit LogLevel ", 0);
    logLevelIntern = logLevel;
    printString_P(logging_getLogLevelName(), 0);
    printNewLine(0);
#endif
}

void logging_setLogLevel(logLevel_t logLevel) {
#if (_DEBUG_MODE)
    logLevelIntern = logLevel;
#endif
}

inline void printString(char* string, uint8_t errorStream) {
    while (*string) {
        if (errorStream) {
            putc(*string, stderr);
        }
        else {
            putc(*string, stdout);
        }
        string++;
    }
}

inline void printString_P(const char* string, uint8_t errorStream) {
    uint8_t currentChar = pgm_read_byte(string);
    while (currentChar != 0) {
        if (errorStream) {
            putc(currentChar, stderr);
        }
        else {
            putc(currentChar, stdout);
        }
        string++;
        currentChar = pgm_read_byte(string);
    }
}

inline void logging_printString(logLevel_t logLevel, char* string) {
#if (_DEBUG_MODE)
    if (logLevel>=logLevelIntern) {
        uint8_t errorStream = (uint8_t)(logLevel >= LOG_ERROR);

        printString_P(logging_getLogLevelName(), errorStream);
        printString(":\t", errorStream);
        printString(string, errorStream);

        printNewLine(errorStream);
    }

    if (logLevel == LOG_FATAL_ERROR) {
        abort();
    }
#endif
}

inline void logging_printString_P(logLevel_t logLevel, const char* string) {
#if (_DEBUG_MODE)
    if (logLevel>=logLevelIntern) {
        uint8_t errorStream = (uint8_t)(logLevel >= LOG_ERROR);

        printString_P(logging_getLogLevelName(), errorStream);
        printString(":\t", errorStream);
        printString_P(string, errorStream);

        printNewLine(errorStream);
    }

    if (logLevel == LOG_FATAL_ERROR) {
        abort();
    }
#endif
}

inline void logging_printStringFileLine(logLevel_t logLevel, char* string, char* file, int line) {
#if (_DEBUG_MODE)
    if (logLevel>=logLevelIntern) {
        uint8_t errorStream = (uint8_t)(logLevel >= LOG_ERROR);

        char stringLine[6];
        itoa(line, stringLine, 10);

        printString_P(logging_getLogLevelName(), errorStream);
        printString(":\t", errorStream);
        printString(string, errorStream);
        printString(", ", errorStream);
        printString(file, errorStream);
        printString(", line: ", errorStream);
        printString(stringLine, errorStream);

        printNewLine(errorStream);
    }

    if (logLevel == LOG_FATAL_ERROR) {
        abort();
    }
#endif
}

void logging_printPartlyStringStart(logLevel_t logLevel, char* string) {
#if (_DEBUG_MODE)
    if (logLevel>=logLevelIntern) {
        uint8_t errorStream = (uint8_t)(logLevel >= LOG_ERROR);

        printString_P(logging_getLogLevelName(), errorStream);
        printString(":\t", errorStream);
        printString(string, errorStream);
    }
#endif
}

void logging_printPartlyStringAppend(logLevel_t logLevel, char* string) {
#if (_DEBUG_MODE)
    if (logLevel>=logLevelIntern) {
        uint8_t errorStream = (uint8_t) (logLevel >= LOG_ERROR);

        printString(string, errorStream);
    }
#endif
}

void logging_printPartlyStringAppend_P(logLevel_t logLevel, const char* string) {
#if (_DEBUG_MODE)
    if (logLevel>=logLevelIntern) {
        uint8_t errorStream = (uint8_t) (logLevel >= LOG_ERROR);

        printString_P(string, errorStream);
    }
#endif
}

void logging_printPartlyNumberUint16Append(logLevel_t logLevel, uint16_t number, uint8_t base) {
#if (_DEBUG_MODE)
    if (logLevel>=logLevelIntern) {
        uint8_t errorStream = (uint8_t) (logLevel >= LOG_ERROR);

        char numberStr[7];
        utoa(number, numberStr, base);
        printString(numberStr, errorStream);
    }
#endif
}

void logging_printPartlyStringEnd(logLevel_t logLevel) {
#if (_DEBUG_MODE)
    if (logLevel>=logLevelIntern) {
        uint8_t errorStream = (uint8_t) (logLevel >= LOG_ERROR);

        printNewLine(errorStream);
    }
#endif
}

const char* logging_getLogLevelName(void) {
#if (_DEBUG_MODE)
    const char* logDebugName = PSTR("DEBUG");
    const char* logInfoName = PSTR("INFO");
    const char* logWarningName = PSTR("WARNING");
    const char* logErrorName = PSTR("ERROR");
    const char* logFatalErrorName = PSTR("FATAL ERROR");
    const char* logDefaultName = PSTR("DEFAULT");

    switch (logLevelIntern) {
        case LOG_DEBUG:
            return logDebugName;
        case LOG_INFO:
            return logInfoName;
        case LOG_WARNING:
            return logWarningName;
        case LOG_ERROR:
            return logErrorName;
        case LOG_FATAL_ERROR:
            return logFatalErrorName;
        default:
            return logDefaultName;
    }
#else
    return PSTR("INFO");
#endif
}

inline void printNewLine(uint8_t errorStream) {
    if (errorStream) {
        putc('\n', stderr);
    }
    else {
        putc('\n', stdout);
    }
}