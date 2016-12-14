#include "module.h"
#include "neopixel.h"
#include "light.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, D7, WS2811);
// necessary to use the led
/////////////////////////////////////////////////////
// called the first time by main to set everythig up correctly
Light::Light(){
	timer = new MyTimer(100);
	setup();
}

/////////////////////////////////////////////////////
// simply setup of variables and functions
void Light :: setup(){
	active = true;
	strip.begin();
	brightness =0;
	color = strip.Color(brightness,brightness,brightness);
}
/////////////////////////////////////////////////////
// Brighter simply causes the light to get brighter whenever called
void Light :: brighter(){

	brightness+=30;
	if(brightness>255)
		brightness=255;
	
}
/////////////////////////////////////////////////////
// the guts of the function, what will be running
void Light :: run(){
	 if(enabled){
	 	color = strip.Color( brightness,brightness,brightness);
		}
	 if(!enabled){
		brightness=0;
		color = strip.Color( 0, 0, 0);
		}
	
	strip.setPixelColor(0, color);
	strip.show();
	
}
/////////////////////////////////////////////////////
// self explanatory past this point, on/off switches
void Light::enable() {
    enabled = true;
}

void Light::disable() {
    enabled = false;
}

