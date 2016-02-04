//#define EXECUTABLE
#define DEBUG
#define EXAMPLE

#ifdef EXECUTABLE
#include <iostream>
#endif

#include "stddef.h"


#ifdef EXAMPLE
#include "example.cpp"
#endif
#ifndef EXAMPLE
#include "sketch.cpp"
#endif


#ifdef DEBUG

static RGB* data;

// for C# unit tests
extern "C" __attribute__((visibility("default")))
int GetActionOutput(uint targetAction, uint* size, RGB** ptr, RGB colorFrom, RGB colorTo, long startTime, uint duration, uint delayAfter, uint tickLength, uint count = 1
        , float upPct = 0.5f, float maxColorPct = 0, float firstColorPct = 0.33f, float secondColorPct = 0.33f) {
    try {
        long currentTime;
        BaseLedAction *action;
        switch (targetAction) {
            case AllowedLedActions::COLOR_CHANGE:
                action = new ColorChangeAction(startTime, duration, colorFrom, colorTo, delayAfter);
                break;
            case AllowedLedActions::STROBE:
                action = new StrobeAction(startTime, duration, colorFrom, colorTo, delayAfter);
                break;
            case AllowedLedActions::STROBE_UNEVEN:
                action = new StrobeUnevenAction(startTime, duration, colorFrom, colorTo, delayAfter, upPct,
                                                maxColorPct);
                break;
            case AllowedLedActions::STROBE_CYCLE:
                action = new StrobeCycleAction(startTime, duration, colorFrom, colorTo, delayAfter, count, upPct,
                                               maxColorPct);
                break;
            case AllowedLedActions::STROBE_RAINBOW:
                action = new StrobeRainbowAction(startTime, duration, delayAfter, count, upPct, maxColorPct);
                break;
            case AllowedLedActions::STROBE_RAINBOW_HALF:
                action = new StrobeRainbowAction(startTime, duration, delayAfter, count, upPct, maxColorPct,
                                                 colorHalfMatrix);
                break;
        }

        uint outputCount = (duration + delayAfter) / tickLength + 1;
        data = new RGB[outputCount];
        for (int i = 0; i < outputCount; i++) {
            currentTime = startTime + i * tickLength;
            data[i] = action->GetCurrentColor(currentTime);
        }
        delete action;
        *size = outputCount;
        *ptr = data;
        return 0;
    }
    catch(int exception) { // pre-defined exceptions. C#/DLLImport cannot catch exceptions in native code.
        return exception;
    }
    catch(...) { // any other exceptions
        return 1;
    }

}

#endif

#ifdef EXECUTABLE
int main(int argc, char * argv[]) {
    // debug test cases
    // DEBUG
    /*
    uint tmpSize;
    RGB* result;
    GetActionOutput(STROBE_UNEVEN, &tmpSize, &result, COLOR_BLACK, COLOR_RED, 1000, 1000, 0, 10, 1, 0.3f, 0.1f);
    for (int i=0; i< tmpSize; i++) {
        RGB color = result[i];
        cout << (int)color.r << "/" << (int)color.g << "/" << (int)color.b << endl;
    }*/
    // END DEBUG

    for (int i=0; i < argc; i++) {
        cout << argv[i] << endl;
    }

    uint actionCount = 0;
    long endTime = 0;
    lazyActionInitializer ** actionTable = BuildActionTable(actionCount, endTime);

    long currentTime = 0;
    ActionWalker walker = ActionWalker(actionTable, actionCount);

    while (currentTime < endTime) {
        RGB color = walker.GetCurrentColor(currentTime);
        cout << (int)color.r << "/" << (int)color.g << "/" << (int)color.b << endl;
        if (currentTime % 100 == 0) {
            cout << "Time: " << currentTime << endl;
        }
        currentTime += 10;
    }
    walker.DestroyTable();
    walker.~ActionWalker();

    return 0;

}

#endif