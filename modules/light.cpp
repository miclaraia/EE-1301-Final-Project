#include "module.h"
#include "neopixel.h"
#include "light.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, D7, WS2811);
Light::Light(){
	timer = new MyTimer(100);
	setup();
	
}
void Light :: setup(){
 //strip = new Adafruit_NeoPixel(1, D7, WS2811);
	//enabled = true;
	active = true;
	strip.begin();
 brightness =0;
 //PixelColor = strip->Color( x, x, x);
color = strip.Color(brightness,brightness,brightness);

}
void Light :: brighter(){
Serial.print(" works");
brightness+=30;
if(brightness>255)
brightness=255;

Serial.print(brightness);
Serial.print(" <- this is the value of brightness");

}
void Light :: run(){

//int color;// = strip.Color(100,100,100);
//Serial.print("Color: ");
//Serial.print(color);
//Serial.print("\n\r");
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

void Light::enable() {
    enabled = true;
}

void Light::disable() {
    enabled = false;
}

