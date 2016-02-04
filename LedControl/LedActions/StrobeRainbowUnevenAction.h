//
// Created by anadorr on 01.02.16.
//

#ifndef LEDCONTROL_STROBERAINBOWUNEVEN_H
#define LEDCONTROL_STROBERAINBOWUNEVEN_H


#include "BaseLedAction.h"

// strobe rainbow colors in batches of 3, with 3 different lengths in batch
class StrobeRainbowUnevenAction : public StrobeRainbowAction {
protected:
    void BuildSchedule() {
        _scheduleLength = 0;
        byte multiplyCount = 3;
        uint batchDelay = Duration / Count;
        uint firstColorDelay = batchDelay * FirstColorPct;
        uint secondColorDelay = batchDelay * SecondColorPct;
        uint thirdColorDelay = batchDelay * ThirdColorPct;

        byte colorCount = (sizeof(colorMatrix) / sizeof(RGB));
        uint tempScheduleCount;
        AbstractScheduler **tempScheduler;
        for (int i = 0; i < Count; i++) {
            tempScheduler = GetStrobe(COLOR_BLACK, colorMatrix[(i+0) % colorCount],StartTime + i * batchDelay, firstColorDelay, tempScheduleCount,
                                                          _upColorPct, _maxColorPct, _downColorPct);
            if (_scheduleLength == 0 || _colorChangeSchedule == NULL) {
                _scheduleLength = tempScheduleCount * Count * multiplyCount;
                _colorChangeSchedule = new AbstractScheduler *[_scheduleLength];
            }
            for (int k = 0; k < tempScheduleCount; k++) {
                _colorChangeSchedule[i * tempScheduleCount * multiplyCount + k + (tempScheduleCount * 0)] = tempScheduler[k];
            }
            delete[] tempScheduler;

            tempScheduler = GetStrobe(COLOR_BLACK, colorMatrix[(i+1) % colorCount],StartTime + i * batchDelay + firstColorDelay, secondColorDelay, tempScheduleCount,
                                      _upColorPct, _maxColorPct, _downColorPct);
            for (int k = 0; k < tempScheduleCount; k++) {
                _colorChangeSchedule[i * tempScheduleCount * multiplyCount + k + (tempScheduleCount * 1)] = tempScheduler[k];
            }
            delete[] tempScheduler;

            tempScheduler = GetStrobe(COLOR_BLACK, colorMatrix[(i+3) % colorCount],StartTime + i * batchDelay + firstColorDelay + secondColorDelay, thirdColorDelay, tempScheduleCount,
                                      _upColorPct, _maxColorPct, _downColorPct);
            for (int k = 0; k < tempScheduleCount; k++) {
                _colorChangeSchedule[i * tempScheduleCount * multiplyCount + k + (tempScheduleCount * 2)] = tempScheduler[k];
            }
            delete[] tempScheduler;
        }

    }

public:
    float FirstColorPct;
    float SecondColorPct;
    float ThirdColorPct;
    StrobeRainbowUnevenAction(long startTime, uint duration, uint delayAfter, byte count, float firstColorPct, float secondColorPct, float upPct = 0.5f,
                              float maxColorPct = 0) :
            StrobeRainbowAction(startTime, duration, delayAfter, count, upPct, maxColorPct) {
        FirstColorPct = firstColorPct;
        SecondColorPct = secondColorPct;
        ThirdColorPct = 1 - firstColorPct - secondColorPct;
    }
};


#endif //LEDCONTROL_STROBERAINBOWUNEVEN_H
