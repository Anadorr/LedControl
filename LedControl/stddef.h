//
// Created by anadorr on 06.12.15.
//

#ifndef LEDCONTROL_STDAFX_H
#define LEDCONTROL_STDAFX_H

#ifdef DEBUG

#define EXCEPTION_ACTION_INCORRECT_TIME_PASSED 100
#define EXCEPTION_ACTION_TABLE_INCORRECT 101
#define EXCEPTION_ACTION_INCORRECT_SCHEDULE_TIME 102

#endif

//#define ARDUINO

#ifndef ARDUINO
using namespace std;
#include <cstdint>
#define abs(a) ((a)<(0)?(-(a)):(a))

#endif

#ifdef ARDUINO

#include "/usr/share/arduino/hardware/arduino/cores/arduino/Arduino.h"

#endif

#define uint unsigned int
#define byte uint8_t
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#include "RGB.h"

#endif