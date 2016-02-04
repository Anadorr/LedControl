//
// Created by anadorr on 01.02.16.
//

#ifndef LEDCONTROL_STROBEACTION_H
#define LEDCONTROL_STROBEACTION_H



#include "BaseLedAction.h"

// change color from colorStart to colorEnd and back to colorStart
class StrobeAction: public BaseLedAction {
protected:
    float _upColorPct;
    float _maxColorPct;
    float _downColorPct;
    void BuildSchedule() {
        _colorChangeSchedule = GetStrobe(ColorStart, ColorEnd, StartTime, Duration, _scheduleLength);
    }
public:
    StrobeAction(long startTime, uint duration, RGB colorStart, RGB colorEnd, uint delayAfter) :
        BaseLedAction(startTime, duration, colorStart, colorEnd, delayAfter) {}
};


#endif //LEDCONTROL_STROBEACTION_H
