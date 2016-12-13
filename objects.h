#ifndef OBJECTS_H_
#define OBJECTS_H_

#include "application.h"

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

struct Button {
    int last = LOW;
    int current = LOW;
    int pin;
};

class MyTimer {
public:
    unsigned int timer;
    int duration;
    bool active;
    void *run();

    bool check();
    void reset();
    void reset(int duration);

    MyTimer(int duration);
};

#endif