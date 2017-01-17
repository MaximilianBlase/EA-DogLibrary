/*! @file logging.h
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

#ifndef MCU_LOGGING_H
#define MCU_LOGGING_H

#include <avr/io.h>

typedef enum {
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL_ERROR
} logLevel_t;

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
