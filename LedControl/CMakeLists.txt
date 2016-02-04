cmake_minimum_required(VERSION 3.2)
project(LedControl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(LedActions)
#include_directories("/usr/share/arduino" "/usr/share/arduino/hardware/arduino/cores/arduino")

file(GLOB_RECURSE SOURCE_FILES
        "*.h"
        "*.cpp"
        )

#add_executable(LedControl ${SOURCE_FILES})
add_library(LedControl STATIC SHARED MODULE ${SOURCE_FILES})