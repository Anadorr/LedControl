//
// Created by anadorr on 06.12.15.
//

#include <stddef.h>
#include "ColorChangeScheduler.h"
// Do not follow RAII because we need lazy loading
void ColorChangeScheduler::Init()
{
    if (_schedule != NULL || _arraySize > 0) return;

    // Division is very expensive on Arduino, so we will determine array index from current time by using bit shift
    byte minArraySize = min((_duration >> _minDesiredPrecisionShift), ColorDifference(_colorStart, _colorEnd) >> 1);

    // precision (time between consecutive color changes) depends on duration, difference between colors and on minimum precision.

    // examples:
    // duration 3 sec, diff 0-255:
    // arraysize = 100, precision = 32

    // duration 5 sec, diff 0 - 10:
    // min arraysize = 10; precision = less than 500 = 256; array size = 19

    // decrease precision until we hit min array size
    _precisionShift = 0;

    uint shiftVal = max(_duration, 1 << _minDesiredPrecisionShift);
    while (shiftVal >= minArraySize && shiftVal >= 1) {
        _arraySize  = shiftVal;
        _precisionShift += 1;
        shiftVal = shiftVal >> 1;
    }
    if (_precisionShift > 0) _precisionShift --;

    _schedule = new RGB[_arraySize];
    _schedule[0] = _colorStart;
    _schedule[_arraySize - 1] = _colorEnd;

    float rShift = ((float)_colorEnd.r - _colorStart.r)/(_arraySize -1);
    float gShift = ((float)_colorEnd.g - _colorStart.g)/(_arraySize -1);
    float bShift = ((float)_colorEnd.b - _colorStart.b)/(_arraySize -1);

    for (int i = 1; i < _arraySize -1; ++i) {
        _schedule[i] = _colorStart;
        _schedule[i].r += rShift * i;
        _schedule[i].g += gShift * i;
        _schedule[i].b += bShift * i;
    }
//    _isInitialized = true;
}

RGB ColorChangeScheduler::GetRGB(long time) {

    if (_schedule == NULL && _arraySize == 0) {
        Init();
    }
    long offset = time - _startTime;

    // to get array index, shift offset by precision
    // e.g. precision = 32 ms (2^5)
    // offset = 11ms -> index = 11 >> 5 = 0
    // offset = 33ms -> index = 1
    // offset = 66ms -> index = 2
    // etc.

    int index = offset >> _precisionShift;
    if (index > _arraySize - 1) return _schedule[_arraySize -1];
    return _schedule[index];
}