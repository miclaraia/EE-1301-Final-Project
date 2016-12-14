#include "definitions.h"
#include "modules.h"


//Module *speaker;

Input *input;
HeartBeat *hb;
Display *display;
Clock *myClock;
Alarm *alarm;
Simon *simon;
Light *light;

int setAlarm(String minutes);
int getAlarm(String input);
int action(String str);

int Module::counter = 0;

bool ran_already = false;


void setup() {
    if (ran_already) {
        delete(input);
        delete(hb);
        delete(display);
        delete(myClock);
        delete(alarm);
        delete(simon);
        delete(light);
    }
    Serial.begin(9600);

    input = new Input();
    hb = new HeartBeat();
    display = new Display();
    myClock = new Clock();
    alarm = new Alarm();
    simon = new Simon();
    light = new Light();

    input->active = true;
    myClock->active = true;
    alarm->active = true;

    myClock->setDisplay(display);
    alarm->setDisplay(display);
    simon->setDisplay(display);

    alarm->setInput(input);
    simon->setInput(input);

    alarm->setSimon(simon);

    alarm->setClock(myClock);


    Particle.function("set_alarm", setAlarm);
    Particle.function("get_alarm", getAlarm);
    Particle.function("action", action);

    ran_already = true;
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
    if (light->check()){
        light->run();
    }

    delay(100);
}

int setAlarm(String minutes) {
    int min = minutes.toInt();
    alarm->setAlarm(min);
    alarm->displayAlarm();
    return 0;
}

int getAlarm(String str) {
    return alarm->getAlarm();
}

int action(String str) {
    if (str.compareTo("trigger") == 0) alarm->trigger();
    else if (str.compareTo("reset") == 0) setup();
    else if (str.compareTo("play") == 0) simon->play();
    else if (str.compareTo("disable") == 0) alarm->disable();
    else if (str.compareTo("enable") == 0) alarm->enable();
}