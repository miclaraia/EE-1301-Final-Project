#include "application.h"

class MyTimer {
public:
    unsigned int timer;
    int duration;
    bool active;
    void *run();

    bool check();
    void reset();

    MyTimer(int duration);
};

class Module {
public:
    bool active = false;
    MyTimer *timer;

    void run();
};

class Input : Module {
    Button buttons[10];
    int last_pressed[LAST_PRESSED_LENGTH];
    int last_pressed_count;
    int count = 0;

    void addButton(Button button);
    void clearPresses();
    void addPress(Button *button);
public:
    Input();

};

struct Button {
    int last = LOW;
    int current = LOW;
    int pin;
}