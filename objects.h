#include "application.h"

class MyTimer {
public:
    unsigned int timer;
    int duration;
    bool active;
    void *run();

    bool check();
    void reset();

    MyTimer(unsigned int timer, int duration);
};

class Module {
public:
    bool run;
    MyTimer timer;

    void run;
}