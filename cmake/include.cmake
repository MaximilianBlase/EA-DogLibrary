cmake_minimum_required(VERSION 2.8)
##################################################################################
#
# Author: Maximilian Blase
# Date: 29.12.2016
#
# This file contains the source include files.
#
# This lines are outsorced to get a more easy readbale head project file in CLion.
# Secondly the head project file should only contain project settings.
##################################################################################

##################################################################################
# include folder
file(GLOB_RECURSE SRC_C_FILES ${PROJECT_SOURCE_DIR}/*_src/*.c)
file(GLOB_RECURSE SRC_CXX_FILES ${PROJECT_SOURCE_DIR}/*_src/*.cpp)
file(GLOB_RECURSE SRC_HEADERS ${PROJECT_SOURCE_DIR}/*_src/*.h)

##################################################################################
# add AVR executable
add_avr_executable(
        ${PROJECT_NAME}
        ${SRC_C_FILES} ${SRC_CXX_FILES} ${SRC_HEADERS}
)

##################################################################################
# debug
# message(FATAL_ERROR ${SRC_C_FILES})