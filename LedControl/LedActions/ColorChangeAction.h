//
// Created by anadorr on 01.02.16.
//

#ifndef LEDCONTROL_COLORCHANGEACTION_H
#define LEDCONTROL_COLORCHANGEACTION_H


#include "BaseLedAction.h"

// change color from one to another
class ColorChangeAction: public BaseLedAction {
protected:
    void BuildSchedule() {
        _scheduleLength = 1;
        _colorChangeSchedule = new AbstractScheduler*[1] { new ColorChangeScheduler(ColorStart, ColorEnd, StartTime, Duration) };
    }
public:
    ColorChangeAction(long startTime, uint duration, RGB colorStart, RGB colorEnd, uint delayAfter) :
            BaseLedAction(startTime, duration, colorStart, colorEnd, delayAfter) {}
};


#endif //LEDCONTROL_COLORCHANGEACTION_H
