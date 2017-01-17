/*
 * author: Maximilian Blase
 * date: 2017 01 17
 */

#ifndef MCU_IODEF_H
#define MCU_IODEF_H

#include <avr/io.h>

// Display

#define DISPPORT        PORTB
#define DISPPIN         PINB
#define DISPDDR         DDRB

#define DISPRESET       PB2
#define DISPA0          PB3
#define DISPCS          PB4
#define DISPMOSI        PB5
#define DISPSCK         PB7

#endif //MCU_IODEF_H
