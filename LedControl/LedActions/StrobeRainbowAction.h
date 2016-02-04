//
// Created by anadorr on 01.02.16.
//

#ifndef LEDCONTROL_STROBERAINBOWACTION_H
#define LEDCONTROL_STROBERAINBOWACTION_H

#include "BaseLedAction.h"

// Strobe rainbow: strobe from black to <color> and back to black for all colors in rainbow table
class StrobeRainbowAction: public StrobeUnevenAction {
protected:
    void BuildSchedule() {
        _scheduleLength = 0;
        uint colorDelay = Duration / Count;
        byte colorCount = (sizeof(colorMatrix)/sizeof(RGB));
        for (int i =0; i < Count; i++) {
            uint tempScheduleCount;
            AbstractScheduler** tempScheduler = GetStrobe(COLOR_BLACK, colorMatrix[i % colorCount], StartTime + i * colorDelay, colorDelay, tempScheduleCount, _upColorPct, _maxColorPct, _downColorPct);
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
    const RGB* ColorTable;
    StrobeRainbowAction(long startTime, uint duration, uint delayAfter, byte count, float upPct = 0.5f, float maxColorPct = 0, const RGB colorTable[] = colorMatrix) :
            StrobeUnevenAction(startTime, duration, COLOR_BLACK, COLOR_BLACK, delayAfter, upPct, maxColorPct)
    {
        Count = count;
        ColorTable = colorTable;
    }

    StrobeRainbowAction(long startTime, uint duration, uint delayAfter, byte count, const RGB colorTable[], float upPct = 0.5f, float maxColorPct = 0) :
            StrobeUnevenAction(startTime, duration, COLOR_BLACK, COLOR_BLACK, delayAfter, upPct, maxColorPct)
    {
        Count = count;
        ColorTable = colorTable;
    }
};

#endif //LEDCONTROL_STROBERAINBOWACTION_H
