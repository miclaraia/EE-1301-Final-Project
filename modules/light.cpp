#include "module.h"
#include "neopixel.h"
#include "light.h"

Light::Light(){
	timer = new MyTimer(200);
	setup();
}
void Light :: setup(){
 strip = new Adafruit_NeoPixel(1, D7, WS2811);
 x =0;
 //PixelColor = strip->Color( x, x, x);


}
void Light :: brighter(){

x+=30;
if(x>255)
x=255;

}
void Light :: run(){

if(enabled){
		 PixelColor = strip->Color( x, x, x);
		 

}
if(!enabled)
 PixelColor = strip->Color( 0, 0, 0);
		
 strip->show();

}

void Light::enable() {
    enabled = true;
}

void Light::disable() {
    enabled = false;
}

