#include "application.h"
#include "definitions.h"

template <class T>
class List {
public:
    int count = 0;
    int max;
    T *list;

    List(int length);
    void add(T t);
    void clear();
    T* get(int index);
};

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



struct Button {
    int last = LOW;
    int current = LOW;
    int pin;
};
