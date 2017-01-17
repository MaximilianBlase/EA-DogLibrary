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

/*******************************************************************************
 * fonts chars
 ******************************************************************************/
extern const fontData_t font_proportional_8px_info;
#define FONT_PROP_8 (&font_proportional_8px_info)
extern const fontData_t font_proportional_16px_info;
#define FONT_PROP_16 (&font_proportional_16px_info)

#endif //MCU_DRAWINGINCLUDE_H
