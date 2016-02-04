//
// Created by anadorr on 06.12.15.
//

#include "BaseLedAction.h"

// prematurely clear schedulers
void BaseLedAction::FreeSchedulers() {
    if (_colorChangeSchedule) {
        for (int i = 0; i < _scheduleLength; i++) {
            if (_colorChangeSchedule[i]) {
                delete _colorChangeSchedule[i];
                _colorChangeSchedule[i] = NULL;
            }
        }
        delete[] _colorChangeSchedule;
        _colorChangeSchedule = NULL;
    }
}

// calculate current colors and return
RGB BaseLedAction::GetCurrentColor(long time) {
    if (_colorChangeSchedule != NULL && _colorChangeSchedule[_scheduleLength - 1]->HasEnded(time)) {
        FreeSchedulers();
        _currentScheduleIndex = 0;
    }

    if (time < StartTime || time > StartTime + Duration) {
#if DEBUG
        throw EXCEPTION_ACTION_INCORRECT_TIME_PASSED;
#endif
        return COLOR_BLACK;
    }

    if (_colorChangeSchedule == NULL) {
        _currentRepeatNum++;
        _currentScheduleIndex = 0;
        BuildSchedule();
    }

    int i = _currentScheduleIndex;
    RGB result = COLOR_BLACK;
    while (i < _scheduleLength) {
        if (_colorChangeSchedule[i]->HasEnded(time)) {
            _colorChangeSchedule[i]->FreeSchedule();
            i++;
            _currentScheduleIndex = i;
            continue;
        }
        result = _colorChangeSchedule[i]->GetRGB(time);
        return result;
        break;
    }
    // for large schedules, we can be few msecs short due to rounding errors (last schedule's end time is less than total end time)
    // determine if this is the case
    long scheduleEndTime = _colorChangeSchedule[i - 1]->GetEndTime();
    long timeTillEnd = StartTime + Duration - time;
    if (time > scheduleEndTime && timeTillEnd >= 0 && timeTillEnd < 100) {
        // return last color
        return _colorChangeSchedule[i - 1]->GetRGB(scheduleEndTime);
    }
#ifdef DEBUG
    throw EXCEPTION_ACTION_INCORRECT_SCHEDULE_TIME; // should never happen!
#endif
}

