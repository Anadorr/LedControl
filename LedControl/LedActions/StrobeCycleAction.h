//
// Created by anadorr on 01.02.16.
//

#ifndef LEDCONTROL_STROBECYCLEACTION_H
#define LEDCONTROL_STROBECYCLEACTION_H

#include "BaseLedAction.h"

// Repeat strobe several times
class StrobeCycleAction: public StrobeUnevenAction {
protected:
    void BuildSchedule() {
        _scheduleLength = 0;
        uint colorDelay = Duration / Count;
        for (int i =0; i < Count; i++) {
            uint tempScheduleCount;
            AbstractScheduler** tempScheduler = GetStrobe(ColorStart, ColorEnd, StartTime + i * colorDelay, colorDelay, tempScheduleCount, _upColorPct, _maxColorPct, _downColorPct);
            if (_scheduleLength == 0 || _colorChangeSchedule == NULL) {
                _scheduleLength = tempScheduleCount * Count;
                _colorChangeSchedule = new AbstractScheduler*[_scheduleLength];
            }
            for (int k=0; k<tempScheduleCount; k++)
            {
                _colorChangeSchedule[i * tempScheduleCount + k] = tempScheduler[k];
            }
            delete[] tempScheduler;
        }
    }
public:
    byte Count;
    StrobeCycleAction(long startTime, uint duration, RGB colorStart, RGB colorEnd, uint delayAfter, byte count, float upPct = 0.5f, float maxColorPct = 0) :
            StrobeUnevenAction(startTime, duration, colorStart, colorEnd, delayAfter, upPct, maxColorPct)
    {
        Count = count;
    }
};


#endif //LEDCONTROL_STROBECYCLEACTION_H
