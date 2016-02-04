//
// Created by anadorr on 01.02.16.
//

#ifndef LEDCONTROL_STROBEUNEVENACTION_H
#define LEDCONTROL_STROBEUNEVENACTION_H

#include "BaseLedAction.h"

// change color from colorStart to colorEnd, wait at max brightness, change back to colorStart
class StrobeUnevenAction: public StrobeAction {
protected:
    void BuildSchedule() {
        _colorChangeSchedule = GetStrobe(ColorStart, ColorEnd, StartTime, Duration, _scheduleLength, _upColorPct, _maxColorPct, _downColorPct);
    }
public:
    StrobeUnevenAction(long startTime, uint duration, RGB colorStart, RGB colorEnd, uint delayAfter, float upPct, float maxColorPct = 0) :
            StrobeAction(startTime, duration, colorStart, colorEnd, delayAfter)
    {
        _upColorPct = upPct;
        _maxColorPct = maxColorPct;
        _downColorPct = 1.0f - upPct - maxColorPct;
    }
};

#endif //LEDCONTROL_STROBEUNEVENACTION_H
