#ifndef LIGHT_H_
#define LIGHT_H_

#include "neopixel.h"
/*
similar to the other header files, this just lists the funtions used by light.cpp
*/
class Light : public Module {

	
	int color; 					// color of the light
	int brightness;				// since we are only changing brightness
	bool enabled = true;		// variable within, to have light on or off
void setup();
public : 
Light();
void brighter();
void enable();
void disable();


void run();
};

#endif