cmake_minimum_required(VERSION 2.8)
##################################################################################
# "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware
# license):
# <dev@layer128.net> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and
# you think this stuff is worth it, you can buy me a be(ve)er(age) in
# return. (I don't like beer much.)
#
# Matthias Kleemann
##################################################################################





##################################################################################
# set project output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

##################################################################################
# name your project
project(EA-DogM-test)

##### TOOLCHAIN SETUP AREA #######################################################
### Set any variables used in the toolchain prior project() call. In that
### case they are already set and used.
##################################################################################

##################################################################################
# tools to be used for programming the AVR
set(AVR_UPLOADTOOL avrdude)
set(AVR_PROGRAMMER usbasp)
set(AVR_UPLOADTOOL_PORT usb)
# AVR and fuses needs to be set
set(AVR_MCU atmega644p)
set(AVR_L_FUSE 0xFF)
#set(AVR_H_FUSE 0xD9) # w/o EESAVE D9
set(AVR_H_FUSE 0xD1) # with EESAVE: D1
set(AVR_EX_FUSE 0xFC)
set(MCU_SPEED "16000000UL")

### END TOOLCHAIN SETUP AREA #####################################################

##################################################################################
# options
option(WITH_MCU "Add the mCU type to the target file name." ON)
option(CXX_NO_THREAD_SAFE_STATICS "Don't use fread save statics in C++" ON)

INCLUDE(cmake/general.cmake)