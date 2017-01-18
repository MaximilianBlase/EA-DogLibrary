Embedded c library that provides the possibility to print everything you want on an Electronic Assembly lc-display with 
128x64 pixel. E.g. text, mathematical figures, or complete pictures. The difference to other existing librarys is, that 
you are not bound to "pages" with 8 pixel height.

# Requirements
* lc-display like EA-DOGL-128
* avr microcontroller like atmel ATmega644pa

# Install
Copy all files from _lcd_src_ and _logging_src_ to your project. If you don't want to have the logging part, then just
remove the folder and delete the now unneeded lines in the lib sources. In the main file, you have to do the init part:
```
dogm_init();
dogmGraphic_init();
draw_font_setCursorXY(0, 0);
draw_font_setCursorLineEnd(DOGM_DISPLAY_WIDTH - 1);
draw_font_setFont(FONT_PROP_8);
```

With that lines, you do the following:
* Init the hardware-part of the display, like spi-communication
* Init the software-part of the display, like representation in ram
* Set the cursor to the top left corner
* Set the line end for the given display
* Select the used font

Also, you need a type of scheduler to periodically flash the new content from ram the the real display. Therefore you
have to call this function as often as needed:
```
dogmGraphic_flushRam()
```

# Usage
Now you can start drawing text, lines, and so on with functions like:
```
draw_font_stringP(DOGM_SET, PSTR("alive.\n"));
```

With that lines, you do the following:
* Draw a given text at that position, where the cursor actual stands
* Use the at last selected font
* Use the mode **DOGM_SET** where other pixels will be cleared, if they have to be white
* Use the progmem space for the string to save not needed ram space
* The char _\n_ sets the cursor to the at last used start position

# Compiling
The compiling was done with the avr-toolchain from atmel with cmake. You can use cmake, or build your own make files, 
like you want.

# Font-structure
_under construction_

# Thanks to
* [cmake-avr](https://github.com/mkleemann/cmake-avr) for the first version of the cmake files
* [lcdlib](https://github.com/mueschel/lcdlib) for the first inspiration and the first font
* [Jan Wiese](https://github.com/jwlighting) for many helpful conversations over several months and some code stuff

# License
**3-Clause BSD License**