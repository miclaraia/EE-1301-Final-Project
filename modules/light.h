#ifndef LIGHT_H_
#define LIGHT_H_

#include "neopixel.h"

class Light : public Module {

	//Adafruit_NeoPixel *strip;
	int color;
	int brightness;
	bool enabled = true;
void setup();
public : 
Light();
void brighter();
void enable();
void disable();


void run();
};

#endif