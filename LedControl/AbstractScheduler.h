//
// Created by anadorr on 02.01.16.
//

#ifndef LEDCONTROL_SCHEDULER_H
#define LEDCONTROL_SCHEDULER_H

#include "stddef.h"

class AbstractScheduler {
protected:
    long _startTime = -1;
    uint _duration = 0;
    AbstractScheduler() {};
    AbstractScheduler(long startTime, uint duration): _startTime(startTime), _duration(duration) {};
public:
    virtual RGB GetRGB(long offset)=0;
    virtual void FreeSchedule()=0;
    virtual ~AbstractScheduler() {}
    long GetEndTime() {return _startTime + _duration;}
    bool HasEnded(long time) { return time > GetEndTime(); }
};


#endif //LEDCONTROL_SCHEDULER_H
