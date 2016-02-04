//
// Created by anadorr on 01.02.16.
//

#ifndef LEDCONTROL_FULLRAINBOWTOHALF_H
#define LEDCONTROL_FULLRAINBOWTOHALF_H


#include "BaseLedAction.h"

// starting from max brightness, decrease brightness to half and proceed to next color
class FullRainbowToHalfAction: public BaseLedAction {
protected:
    void BuildSchedule() {
        _scheduleLength = Count;
        uint colorDelay = Duration / Count;
        byte colorCount = (sizeof(colorMatrix)/sizeof(RGB));
        _colorChangeSchedule = new AbstractScheduler*[_scheduleLength];

        AbstractScheduler** tempScheduler = new AbstractScheduler*[_scheduleLength];
        byte i = 0;

        for (i=0; i < _scheduleLength; i++) {
            _colorChangeSchedule[i]= new ColorChangeScheduler( colorMatrix[i % colorCount], colorHalfMatrix[ i % colorCount], StartTime + i * colorDelay, colorDelay );
        }
        delete tempScheduler;
    }
public:
    byte Count;
    FullRainbowToHalfAction(long startTime, uint duration, uint delayAfter, byte count) :
            BaseLedAction(startTime, duration, COLOR_BLACK, COLOR_BLACK, delayAfter)
    {
        Count = count;
    }
};


#endif //LEDCONTROL_FULLRAINBOWTOHALF_H
