#include "objects.h"

// %%%%%%%%%%%%% LIST

template<class T>
List<T>::List(int length) {
    this->max = length;
    list = new T[length];
}

template<class T>
void List<T>::add(T t) {
    if (count < max) {
        list[count] = t;
        count++;
    }
}

template<class T>
void List<T>::clear() {
    count = 0;
}

template<class T>
T * List<T>::get(int index) {
    return &list[index];
}

template class List<int>;
template class List<Button>;

// %%%%%%%%%%%%% TIMER

MyTimer::MyTimer(int duration) {
    this->duration = duration;
    reset();
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

void MyTimer::reset(int duration) {
    this->duration = duration;
    reset();
}