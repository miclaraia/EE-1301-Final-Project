#include "modules.h"

HeartBeat::HeartBeat() {
    active = true;
    timer = new MyTimer(500);
}
void HeartBeat::run() {
    if (state) digitalWrite(D7, HIGH);
    else digitalWrite(D7, LOW);

    state = !state;
}