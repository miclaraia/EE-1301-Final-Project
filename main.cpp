#include "definitions.h"
#include "objects.h"
#include <sstream>
#include <string>

Module *myClock;
Module *simon;
Module *speaker;
Input *input;

HeartBeat *hb;

void setup() {
    Serial.begin(9600);

    input = new Input();
    hb = new HeartBeat();
    input->active = true;

    pinMode(D7, OUTPUT);



    Particle.variable("tempval", input->last_pressed->list);
}

void loop() {
    std::stringstream ss;
    ss << "Running \n";
    std::string s = ss.str();
    //Serial.print(s.c_str());
    if (input->timer->check()) {
        input->run();
    }

    if (hb->timer->check()) {
        hb->run();
    }

    delay(100);
}