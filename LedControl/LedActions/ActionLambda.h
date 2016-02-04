//
// Created by anadorr on 04.02.16.
//

#ifndef LEDCONTROL_ACTIONLAMBDA_H
#define LEDCONTROL_ACTIONLAMBDA_H

#include "BaseLedAction.h"

using ptrActionFunc = BaseLedAction*(*)();

struct lazyActionInitializer {
public:
    ptrActionFunc actionLambda;
    BaseLedAction* GetUnderlyingAction() {
        return (*actionLambda)();
    }
    lazyActionInitializer(ptrActionFunc f){
        actionLambda = f;
    }
};

class ActionWalker {
    BaseLedAction* _currentAction;
    int _currentCount;
    lazyActionInitializer** _actionTable;
    uint _actionCount;
public:
    ActionWalker(lazyActionInitializer** actionTable, uint actionCount) {
        _currentAction = NULL;
        _currentCount = -1;
        _actionTable = actionTable;
        _actionCount = actionCount;
    }

    // Walker is only responsible for current action
    ~ActionWalker() {
        if (_currentAction != NULL) {
            delete _currentAction;
            _currentAction = NULL;
        }
    }

    // Call this if you want to destroy action table but lazy to do so yourself
    void DestroyTable() {
        if (_actionTable == NULL) return;
        for (int i=0; i<_actionCount; i++) {
            if (_actionTable[i] != NULL) {
                delete _actionTable[i];
                _actionTable[i] = NULL;
            }
        }
        delete[] _actionTable;
        _actionTable = NULL;
    }

    RGB GetCurrentColor(long time) {
        if (_currentAction != NULL && time >= _currentAction->StartTime && time <= _currentAction->EndTime) {
            return _currentAction->GetCurrentColor(time);
        }

        if (_currentAction == NULL || time > _currentAction->EndTime) {
            long estimatedLastEndTime = 0;
            while (_currentCount < (int)_actionCount) {
                if (_currentAction != NULL) { // delete old action
                    estimatedLastEndTime = _currentAction->EndTime;
                    //_currentAction->FreeSchedulers();
                    delete _currentAction;
                    _currentAction = NULL;
                }

                _currentCount++;

                // Get next action
                if (_actionTable[_currentCount] == NULL) continue;
                _currentAction = _actionTable[_currentCount]->GetUnderlyingAction();

                // Get to next not-null action
                if (_currentAction != NULL) {
#ifdef DEBUG
                    if (estimatedLastEndTime > 0 && _currentAction->StartTime != estimatedLastEndTime) {
                        throw EXCEPTION_ACTION_TABLE_INCORRECT;
                    }
#endif
                    // Get color
                    if (time >= _currentAction->StartTime && time <= _currentAction->EndTime) {
                        return _currentAction->GetCurrentColor(time);
                    }
                }
            }
        }
        // Should never get here
        return COLOR_BLACK;
#ifdef DEBUG
        throw EXCEPTION_ACTION_INCORRECT_TIME_PASSED;
#endif
    }

};

#endif //LEDCONTROL_ACTIONLAMBDA_H
