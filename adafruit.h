#ifndef LED_ON
#include "adafruit-led-backpack.h"
#endif

typedef Adafruit_8x8matrix Matrix;

#ifndef ADAFRUIT_H_
#define ADAFRUIT_H_
static const uint8_t PROGMEM bmp_x[] =
{
    B10000001,
    B01000010,
    B00100100,
    B00011000,
    B00011000,
    B00100100,
    B01000010,
    B10000001,
};

static const uint8_t PROGMEM bmp_1[] =
{
    B00100000,
    B01100000,
    B10100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000,
    B00100000
};

static const uint8_t PROGMEM bmp_2[] =
{
    B11110000,
    B00010000,
    B00010000,
    B11110000,
    B10000000,
    B10000000,
    B10000000,
    B11110000
};

static const uint8_t PROGMEM bmp_3[] =
{
    B11110000,
    B00010000,
    B00010000,
    B11110000,
    B00010000,
    B00010000,
    B00010000,
    B11110000
};

static const uint8_t PROGMEM bmp_4[] =
{
    B10010000,
    B10010000,
    B10010000,
    B11110000,
    B00010000,
    B00010000,
    B00010000,
    B00010000
};



#endif
