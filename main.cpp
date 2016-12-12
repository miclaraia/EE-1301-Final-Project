#include "definitions.h"
#include "includes.h"

Module *simon;
Module *speaker;
Input *input;

HeartBeat *hb;
Display *display;
Clock *myClock;


void setup() {
    Serial.begin(9600);

    input = new Input();
    hb = new HeartBeat();
    display = new Display();
    myClock = new Clock();

    input->active = true;
    myClock->active = true;
    myClock->setDisplay(display);

    pinMode(D7, OUTPUT);


}

void loop() {
    Serial.print("running");
    //Serial.print(s.c_str());
    if (input->check()) {
        input->run();
    }

    if (display->check()) {
        display->run();
    }

    if (hb->check()) {
        hb->run();
    }

    if (myClock->check()) {
        myClock->run();
    }

    delay(100);
}