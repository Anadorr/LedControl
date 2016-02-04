//
// Created by anadorr on 01.02.16.
//

#ifndef LEDCONTROL_FULLRAINBOWACTION_H
#define LEDCONTROL_FULLRAINBOWACTION_H

#include "BaseLedAction.h"

// Full rainbow: change rainbow colors from one to another without black in between
class FullRainbowAction: public BaseLedAction {
protected:
    void BuildSchedule() {
        _scheduleLength = Count;
        uint colorDelay = Duration / Count;
        byte colorCount = (sizeof(colorMatrix)/sizeof(RGB));
        _colorChangeSchedule = new AbstractScheduler*[_scheduleLength];

        AbstractScheduler** tempScheduler = new AbstractScheduler*[_scheduleLength];
        byte i = 0;
        _colorChangeSchedule[0] = new ColorChangeScheduler( colorMatrix[i % colorCount], colorMatrix[(i+1) % colorCount], StartTime+ i * colorDelay, colorDelay );
        for (i=1; i <= _scheduleLength - 2; i++) {
            _colorChangeSchedule[i]= new ColorChangeScheduler( colorMatrix[i % colorCount], colorMatrix[(i+1) % colorCount], StartTime + i * colorDelay, colorDelay );
        }
        _colorChangeSchedule[_scheduleLength -1] = new ColorChangeScheduler( colorMatrix[i % colorCount], COLOR_BLACK, StartTime + i * colorDelay, colorDelay );
        delete tempScheduler;
    }
public:
    byte Count;
    FullRainbowAction(long startTime, uint duration, uint delayAfter, byte count) :
            BaseLedAction(startTime, duration, COLOR_BLACK, COLOR_BLACK, delayAfter)
    {
        Count = count;
    }
};


#endif //LEDCONTROL_FULLRAINBOWACTION_H
