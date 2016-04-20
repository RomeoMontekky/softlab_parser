﻿cmake_minimum_required(VERSION 3.0)

project(softlab_parser)

set(BINARY_NAME "softlab_parser")

set(CPP_FILES
   "./exception.cpp"
   "./main.cpp"
   "./parser.cpp"
)

set(HEADER_FILES
   "./exception.h"
   "./parser.h"
)

add_executable(${BINARY_NAME} ${CPP_FILES} ${HEADER_FILES})

if (MINGW)
   if (CMAKE_BUILD_TYPE STREQUAL "Release")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++14")
      add_custom_command(
         TARGET ${BINARY_NAME} POST_BUILD
         COMMAND ${CMAKE_STRIP} ARGS "--strip-unneeded" "$<TARGET_FILE:${BINARY_NAME}>")
   else()
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++14")
   endif()
else()
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_SCL_SECURE_NO_WARNINGS")
endif()

