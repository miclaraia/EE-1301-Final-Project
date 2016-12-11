#include "objects.h"

MyTimer::MyTimer(int duration) {
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