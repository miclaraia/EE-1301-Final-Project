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

struct Button;
class Input : Module {
    List<Button> buttons;
    List<int> last_pressed;

public:
    Input();

    void addButton(Button button);
    void clearPresses();
    void addPress(Button *button);

};

struct Button {
    int last = LOW;
    int current = LOW;
    int pin;
}

template <class T>
class List {
public:
    int count = 0;
    int max;
    T *list;

    List(int length);
    void add(T t);
    void clear();
    *T get(int index);
}