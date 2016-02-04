//
// Created by anadorr on 06.12.15.
//

#ifndef LEDCONTROL_RGB_H
#define LEDCONTROL_RGB_H

//#include "stdafx.h"

struct RGB {
    byte r;
    byte g;
    byte b;
};

static const RGB COLOR_WHITE = (RGB) {255, 255, 255};
static const RGB COLOR_HWHITE = (RGB) {63, 63, 63};
static const RGB COLOR_YELLOW = (RGB) {255, 255, 0};
static const RGB COLOR_HYELLOW = (RGB) {63, 63, 0};
static const RGB COLOR_ORANGE = (RGB) {255, 128, 0};
static const RGB COLOR_HORANGE = (RGB) {63, 31, 0};
static const RGB COLOR_RED = (RGB) {255, 0, 0};
static const RGB COLOR_HRED = (RGB) {63, 0, 0};
static const RGB COLOR_GREEN = (RGB) {0, 255, 0};
static const RGB COLOR_HGREEN = (RGB) {0, 63, 0};
static const RGB COLOR_BLUE = (RGB) {0, 0, 255};
static const RGB COLOR_HBLUE = (RGB) {0, 0, 63};
static const RGB COLOR_BLACK = (RGB) {0, 0, 0};
static const RGB COLOR_PINK = (RGB) {255, 0, 255};
static const RGB COLOR_HPINK = (RGB) {63,0,63};
static const RGB COLOR_VIOLET = (RGB) {128, 0, 255};
static const RGB COLOR_HVIOLET = (RGB) {31,0,63};
static const RGB COLOR_MAGENTA = (RGB) {255, 0, 128};
static const RGB COLOR_HMAGENTA = (RGB) {63,0,31};

static const RGB colorMatrix[] = {
        COLOR_RED, //red
        COLOR_YELLOW, //yellow
        COLOR_BLUE, //blue
        COLOR_PINK, //pink
        COLOR_ORANGE, //orange
        COLOR_VIOLET, //violet
        COLOR_GREEN, //green
        COLOR_MAGENTA, //magenta
        COLOR_WHITE
};

static const RGB randomColorMatrix[] = {
        COLOR_RED,
        COLOR_YELLOW,
        COLOR_BLUE,
        COLOR_PINK,
        COLOR_ORANGE,
        COLOR_VIOLET,
        COLOR_GREEN,
        COLOR_MAGENTA,
        COLOR_WHITE
};

static const RGB colorHalfMatrix[] = {
        COLOR_HRED,
        COLOR_HYELLOW,
        COLOR_HBLUE,
        COLOR_HPINK,
        COLOR_HORANGE,
        COLOR_HVIOLET,
        COLOR_HGREEN,
        COLOR_HMAGENTA,
        COLOR_HWHITE
};


static byte ColorDifference(RGB& color1, RGB& color2) {
    byte d1 = abs((int)color1.r - color2.r);
    if (d1 == 255) return d1;
    byte d2 = abs((int)color1.g - color2.g);
    if (d2 == 255) return d2;
    byte d3 = abs((int)color1.b - color2.b);
    if (d3 == 255) return d3;
    return max(max(d1,d2), d3);
}

#endif //LEDCONTROL_RGB_H
