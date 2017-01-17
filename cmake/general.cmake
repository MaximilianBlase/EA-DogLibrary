cmake_minimum_required(VERSION 2.8)
##################################################################################
#
# Author: Maximilian Blase
# Date: 07.02.2016
#
# This file contains general content for cmake.
#
# This lines are outsorced to get a more easy readbale head project file in CLion.
# Secondly the head project file should only contain project settings.
##################################################################################
set(CMAKE_BUILD_TYPE RELEASE)

##################################################################################
# Linux -rdynamic fix
# https://cmake.org/Bug/view.php?id=9985
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

##################################################################################
# include general cmake CLion functions
INCLUDE(cmake/generic-gcc-avr.cmake)
include_directories(${PROJECT_SOURCE_DIR}/logging_src)

##################################################################################
# add all needed sources and headers
INCLUDE(cmake/include.cmake)

##################################################################################
# add AVR library
if (APPLE)

    if (${AVR_MCU} STREQUAL atmega1284p)
        #fix 128kb flash
        set(C_LIB /usr/local/Cellar/avr-libc/2.0.0/avr/lib/avr51/libc.a)
    else ()
        # normal
        set(C_LIB /usr/local/Cellar/avr-libc/2.0.0/avr/lib/libc.a)
    endif ()
elseif (UNIX)

    if (${AVR_MCU} STREQUAL atmega1284p)
        #fix 128kb flash
        set(C_LIB /usr/lib/avr/lib/avr51/libc.a)
    else ()
        # normal
        set(C_LIB /usr/lib/avr/lib/libc.a)
    endif ()
else ()
    find_library(C_LIB c)
endif (APPLE)

##################################################################################
# link AVR library
avr_target_link_libraries(${PROJECT_NAME} ${C_LIB})

##################################################################################
# add AVR library
# NOTE: deprecated
#add_avr_library(
#   <library-name>
#   <sources> <headers>
#)

##################################################################################
# link library to executable
# NOTE: It needs to be the elf target.
# NOTE: Deprecated
# target_link_libraries(<executable-name>-${AVR_MCU}.elf <library-name>-${AVR_MCU})