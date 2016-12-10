#include "timer.h"
#include "application.h"

MyTimer::MyTimer(unsigned int timer, int duration) {
    this->timer = timer;
    this->duration = duration;
}

bool MyTimer::check() {
    if (timer <= millis()) {
        reset();
        return true;
    }

    return false;
}

void MyTimer::reset() {
    timer = millis() + duration;
}