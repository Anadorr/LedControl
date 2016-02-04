//
// Created by anadorr on 06.12.15.
//

#ifndef LEDCONTROL_COLORCHANGESCHEDULER_H
#define LEDCONTROL_COLORCHANGESCHEDULER_H

#include "AbstractScheduler.h"

// 'Dumb' scheduler class. Holds color sequence (schedule) to be shown to change from <colorStart> to <colorEnd> in <duration> time.
// Schedule is initialized and freed at once.
// Each instance of this class takes 36 bytes,
// so it's better to have no more than 30 instances allocated at any time.
// Strobe creates 2 instances.

// Arduino has a 8-bit architecture. Uncomment this to determine class size in Arduino on x86.
// #pragma pack(1)

class ColorChangeScheduler: public AbstractScheduler {
    RGB* _schedule = 0; // array of pre-calculated colors

    RGB _colorStart;
    RGB _colorEnd;

    byte _arraySize = 0;
    byte _precisionShift; // how many bits to shift offset to get array index; usually 5/6/7

    void Init();
    static const byte _minDesiredPrecisionShift = 5; // minimum granularity = 32ms

public:
    ColorChangeScheduler(): AbstractScheduler() {}; // default parameterless constructor for array init
    ColorChangeScheduler(const RGB& colorStart, const RGB& colorEnd, long startTime, uint duration): AbstractScheduler(startTime, duration), _colorStart(colorStart), _colorEnd(colorEnd)
            {};

    ~ColorChangeScheduler() {
        FreeSchedule();
    }
    // free memory earlier because Arduino can't hold many schedules at once
    void FreeSchedule() {
        if (_schedule) {
            delete[] _schedule;
            _schedule = NULL;
        }
    }

    RGB GetRGB(long offset);
};


#endif //LEDCONTROL_COLORCHANGESCHEDULER_H
