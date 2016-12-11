#include definitions.h
#include timer.h

Module *clock;
Module *simon;
Module *speaker;

void setup() {

}

void loop() {
    if (simon->timer->check()) {
        simon->run();
    }
}