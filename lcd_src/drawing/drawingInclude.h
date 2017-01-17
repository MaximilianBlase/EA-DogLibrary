/*! @file drawingInclude.h
 *
 * @author Maximilian Blase
 * @date 2016-02-24
 * @copyright
 *  2016 M.Blase
 *
 * @date 2016-02-24
 * @note This file defines all global used extern sources, like:
 *  * images
 *  * logos
 *  * symbols
 *  * fonts
 */

#ifndef MCU_DRAWINGINCLUDE_H
#define MCU_DRAWINGINCLUDE_H

#include "drawingFigures.h"
#include "drawingText.h"

/*******************************************************************************
 * logos
 ******************************************************************************/

/*******************************************************************************
 * pictures
 ******************************************************************************/

/*******************************************************************************
 * symbols
 ******************************************************************************/
extern const imageData_t symbol_abort;
extern const imageData_t symbol_back;
extern const imageData_t symbol_diskette;
extern const imageData_t symbol_diskette_write;
extern const imageData_t symbol_diskette_read;
extern const imageData_t symbol_dummy;
extern const imageData_t symbol_home;
extern const imageData_t symbol_menu;
extern const imageData_t symbol_ok;
extern const imageData_t symbol_standby;
extern const imageData_t symbol_usbstick;
extern const imageData_t symbol_reset;

/*******************************************************************************
 * fonts chars
 ******************************************************************************/
extern const fontData_t font_proportional_8px_info;
#define FONT_PROP_8 (&font_proportional_8px_info)
extern const fontData_t font_proportional_16px_info;
#define FONT_PROP_16 (&font_proportional_16px_info)

#endif //MCU_DRAWINGINCLUDE_H
