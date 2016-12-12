#include "definitions.h"
#include "includes.h"
#include <sstream>
#include <string>

Module *myClock;
Module *simon;
Module *speaker;
Input *input;

HeartBeat *hb;
Display *display;

void setup() {
    Serial.begin(9600);

    input = new Input();
    hb = new HeartBeat();
    display = new Display();
    
    input->active = true;

    pinMode(D7, OUTPUT);
}

void loop() {
    std::stringstream ss;
    ss << "Running \n";
    std::string s = ss.str();
    //Serial.print(s.c_str());
    if (input->timer->check()) {
        input->run();
    }

    if (display->timer->check()) {
        display->run();
    }

    if (hb->timer->check()) {
        hb->run();
    }

    delay(100);
}