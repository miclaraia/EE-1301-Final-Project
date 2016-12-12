#include "definitions.h"
#include "includes.h"

Module *speaker;
Input *input;

HeartBeat *hb;
Display *display;
Clock *myClock;
Alarm *alarm;
Simon *simon;

int setAlarm(String minutes);
int getAlarm(String input);


void setup() {
    Serial.begin(9600);

    input = new Input();
    hb = new HeartBeat();
    display = new Display();
    myClock = new Clock();
    alarm = new Alarm();
    Simon = new Simon();

    input->active = true;
    myClock->active = true;
    alarm->active = true;

    myClock->setDisplay(display);
    alarm->setDisplay(display);

    alarm->setInput(input);

    pinMode(D7, OUTPUT);


    Particle.function("set_alarm", setAlarm);
    Particle.function("get_alarm", getAlarm);
}

void loop() {
    //Serial.print("running");
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

    if (alarm->check()) {
        alarm->run();
    }

    if (simon->check()) {
        simon->run();
    }

    delay(100);
}

int setAlarm(String minutes) {
    //alarm->setAlarm(minutes);
    return 0;
}

int getAlarm(String str) {
    return alarm->getAlarm();
}