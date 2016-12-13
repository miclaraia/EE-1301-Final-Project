#include "module.h"
#include "debug.h"

Module::Module() {
    setid();
}

bool Module::check() {
    return active && timer->check();
}

void Module::setid() {
    this->id = counter;
    counter++;
}

HeartBeat::HeartBeat() {
    active = true;
    timer = new MyTimer(500);
    setid();
}
void HeartBeat::run() {
    if (state) digitalWrite(D7, HIGH);
    else digitalWrite(D7, LOW);

    state = !state;
}
