//
// Created by anadorr on 06.12.15.
//

#ifndef LEDCONTROL_LEDACTIONS_H
#define LEDCONTROL_LEDACTIONS_H

#include <string.h>
#include "../stddef.h"
#include "../AbstractScheduler.h"
#include "../ColorChangeScheduler.h"


enum AllowedLedActions {
    COLOR_CHANGE, STROBE, STROBE_UNEVEN, STROBE_CYCLE,  STROBE_RAINBOW, FULL_RAINBOW, STROBE_RAINBOW_HALF
};

class BaseLedAction {

protected:
    AbstractScheduler** _colorChangeSchedule = 0;

    uint _scheduleLength;
    byte _currentScheduleIndex = 0;
    uint _currentRepeatNum = 0;

    virtual void BuildSchedule() =0;
    // Strobe scheduling is reused by many actions
    static AbstractScheduler** GetStrobe(RGB colorFrom, RGB colorTo, long startTime, uint duration, uint& scheduleCount, float upPct = 0.5, float brightPct = 0, float downPct = 0.5) {
        scheduleCount = 2;
        if (brightPct > 0) {
            scheduleCount = 3;
        }
        uint warmupTime = duration * upPct;
        uint fullColorTime = duration * brightPct;
        uint downTime = duration * downPct;

        AbstractScheduler** scheduler = new AbstractScheduler*[scheduleCount];
        byte i = 0;
        scheduler[i++] = new ColorChangeScheduler( colorFrom, colorTo, startTime, warmupTime);
        if (brightPct > 0) {
            scheduler[i++] = new ColorChangeScheduler( colorTo, colorTo, startTime + warmupTime, fullColorTime);
        }
        scheduler[i++] = new ColorChangeScheduler( colorTo, colorFrom, startTime + warmupTime + fullColorTime, downTime);
        return scheduler;
    }


public:
    RGB ColorStart;
    RGB ColorEnd;
    long StartTime;
    long EndTime;
    uint Duration;
    uint DelayAfter;

    BaseLedAction() {}
    BaseLedAction(long startTime, uint duration, RGB colorStart, RGB colorEnd, uint delayAfter)
            : StartTime(startTime), Duration(duration), ColorStart(colorStart), ColorEnd(colorEnd), DelayAfter(delayAfter), EndTime(startTime + duration + delayAfter) {}

    ~BaseLedAction() {
        FreeSchedulers();
    }
    void FreeSchedulers();

    RGB GetCurrentColor(long time);

    static AllowedLedActions ToEnum(char* string) {
        if (strcmp(string, "STROBE") == 0)
            return STROBE;
        if (strcmp(string, "STROBE_UNEVEN") == 0)
            return STROBE_UNEVEN;
        if (strcmp(string, "COLOR_CHANGE") == 0)
            return COLOR_CHANGE;
        if (strcmp(string, "FULL_RAINBOW") == 0)
            return FULL_RAINBOW;
        if (strcmp(string, "STROBE_RAINBOW") == 0)
            return STROBE_RAINBOW;
        if (strcmp(string, "STROBE_CYCLE") == 0)
            return STROBE_CYCLE;
        return STROBE;
    }
};


#endif //LEDCONTROL_LEDACTIONS_H
