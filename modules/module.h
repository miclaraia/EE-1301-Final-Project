#ifndef MODULE_H_
#define MODULE_H_

#include "adafruit.h"
#include "definitions.h"
#include "objects.h"
#include "neopixel.h"

class Module {
public:
    bool active = false;
    MyTimer *timer;
    int id;

    Module();

    bool check();
    void run();
    void setup();
    void setid();

    static int counter;
};

/**
 * Module to flash a heartbeat led
 */
class HeartBeat : public Module {
    bool state = true;
public:
    HeartBeat();
    void run();
};

class Speaker : public Module {

};

#endif