#include "objects.h"
#include "definitions.h"

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

Input::Input() {
    buttons = List<Button>(5);
    last_pressed = List<int>(LAST_PRESSED_LENGTH);

    timer = new MyTimer(100);
    Button button;

    button.pin = BUTTON_TOPLEFT;
    addButton(button);

    button.pin = Button_TOPRIGHT;
    addButton(button);

    button.pin = Button_BOTTOMRIGHT;
    addButton(button);

    button.pin = Button_BOTTOMLEFT;
    addButton(button);

    button.pin = Button_SNOOZE;
    addButton(button);
}

void Input::addButton(Button button) {
    buttons.add(button);
}

void Input::addPress(Button *button) {
    if (lassed_pressed.count + 1 >= last_pressed.max) {
        for (int i = 1; i < last_pressed.count; i++) {
            last_pressed.list[i - 1] = last_pressed.list[i];
        }
    }

    last_pressed.list[last_pressed.count - 1] = button->pin;
}

void Input::clearPresses() {
    last_pressed.clear();
}

Input::run() {
    if (active) {
        Button *button;
        for (int i = 0; i < count; i++) {
            button = buttons.get(i);
            button->current = digitalRead(BUTTON);

            if (button->current == HIGH && button->last == LOW) {
                addPress(button);

            button->last = button->current;
        }
    }
}