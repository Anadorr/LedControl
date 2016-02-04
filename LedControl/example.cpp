//
// Created by anadorr on 04.02.16.
//

#include "LedActions/ActionLambda.h"
#include "LedActions/actions.h"

static lazyActionInitializer ** BuildActionTable(uint& actionCount, long& endTime) {
    actionCount = 13;

    lazyActionInitializer ** arr = new lazyActionInitializer *[actionCount];
    int i=0;
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new ColorChangeAction(0, 1000, COLOR_BLACK, COLOR_WHITE, 0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeAction(1000, 1000, COLOR_RED, COLOR_GREEN, 0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeUnevenAction(2000, 1000, COLOR_HBLUE, COLOR_MAGENTA, 0, 0.3f,0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeAction(3000, 1000, COLOR_WHITE, COLOR_BLACK, 0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeAction(4000, 1000, COLOR_HORANGE, COLOR_WHITE, 0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeAction(5000, 1000, COLOR_BLACK, COLOR_WHITE, 0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeAction(6000, 1000, COLOR_RED, COLOR_GREEN, 0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeAction(7000, 1000, COLOR_BLACK, COLOR_WHITE, 0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeAction(8000, 1000, COLOR_RED, COLOR_GREEN, 0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeAction(9000, 1000, COLOR_BLACK, COLOR_WHITE, 0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeAction(10000, 1000, COLOR_RED, COLOR_GREEN, 0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeAction(11000, 1000, COLOR_BLACK, COLOR_WHITE, 0); });
    arr[i++]  = new lazyActionInitializer([] ()->BaseLedAction* { return new StrobeAction(12000, 1000, COLOR_RED, COLOR_GREEN, 0); });
    endTime = 13000;
    return arr;
}