#include "module.h"
#include "input.h"
#include "debug.h"
#include "application.h"

Input::Input() {
    setid();
    setup();
}

void Input::setup() {
    buttons = new List<Button>(10);
    last_pressed = new List<int>(LAST_PRESSED_LENGTH);

    timer = new MyTimer(100);
    Button button;

    button.pin = BUTTON_TOPLEFT;
    addButton(button);

    button.pin = BUTTON_TOPRIGHT;
    addButton(button);

    button.pin = BUTTON_BOTTOMRIGHT;
    addButton(button);

    button.pin = BUTTON_BOTTOMLEFT;
    addButton(button);

    button.pin = BUTTON_SNOOZE;
    addButton(button);

    initButtons();
}

void Input::initButtons() {
    for (int i = 0; i < buttons->count; i++) {
        int pin = buttons->get(i)->pin;
        pinMode(pin, INPUT_PULLDOWN);
    }
}

void Input::addButton(Button button) {
    buttons->add(button);
}

void Input::addPress(Button *button) {
    debugButton(button->pin);
    if (button->pin == BUTTON_SNOOZE) {
        debugArray(last_pressed->list, last_pressed->count);
        last_pressed->clear();
    }


    if (last_pressed->count + 1 >= last_pressed->max) {
        for (int i = 1; i < last_pressed->count; i++) {
            last_pressed->list[i - 1] = last_pressed->list[i];
        }
        last_pressed->count--;
    }

    last_pressed->list[last_pressed->count] = button->pin;
    last_pressed->count++;
}

void Input::clearPresses() {
    last_pressed->clear();
}

void Input::run() {
    if (active) {
        Button *button;
        for (int i = 0; i < buttons->count; i++) {
            button = buttons->get(i);

            button->current = digitalRead(button->pin);

            if (button->current == HIGH && button->last == LOW) {
                //std::stringstream ss;
                //ss << "i: " << i;
                //debug(&ss);
                addPress(button);
            }

            button->last = button->current;
        }
    }
}