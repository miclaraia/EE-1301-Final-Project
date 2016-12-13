#include "module.h"
#include "debug.h"

Module::Module() {
    setid();
}

/**
 * Check if the module should be run:
 * if it is active and if the timer has passed
 */
bool Module::check() {
    return active && timer->check();
}

/**
 * Assign a unique id number to this module
 */
void Module::setid() {
    this->id = counter;
    counter++;
}

HeartBeat::HeartBeat() {
    active = true;
    timer = new MyTimer(500);
    setid();
}

/**
 * Flashes the D7 LED for debugging, to show the code is running
 */
void HeartBeat::run() {
    if (state) digitalWrite(D7, HIGH);
    else digitalWrite(D7, LOW);

    state = !state;
}
