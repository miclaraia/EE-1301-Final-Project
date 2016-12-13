#include "module.h"
#include "input.h"
#include "debug.h"
#include "application.h"

Input::Input() {
    setup();
}

/**
 * Initialize variables
 */
void Input::setup() {
    // Create button List
    buttons = new List<Button>(10);
    /**
     * List that keeps track of the most recent button presses.
     * When the list fills up, The array is shifted left
     * (dropping the oldest button) to make room.
     */
    last_pressed = new List<int>(LAST_PRESSED_LENGTH);

    // Create timer
    timer = new MyTimer(100);

    // Initialize buttons and their pins
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

/**
 * Initialize the pinmode of all the buttons
 */
void Input::initButtons() {
    for (int i = 0; i < buttons->count; i++) {
        int pin = buttons->get(i)->pin;
        pinMode(pin, INPUT_PULLDOWN);
    }
}

/**
 * Add button to array
 */
void Input::addButton(Button button) {
    buttons->add(button);
}

/**
 * Register that a button was pressed and add it to
 * the last_pressed array
 */
void Input::addPress(Button *button) {
    debugButton(button->pin);

    if (button->pin == BUTTON_SNOOZE) {
        debugArray(last_pressed->list, last_pressed->count);
        //last_pressed->clear();
    }

    // Shifts array if count reaches max
    if (last_pressed->count + 1 >= last_pressed->max) {
        for (int i = 1; i < last_pressed->count; i++) {
            last_pressed->list[i - 1] = last_pressed->list[i];
        }
        last_pressed->count--;
    }

    // Add button pin to the end
    last_pressed->list[last_pressed->count] = button->pin;
    last_pressed->count++;
}

/**
 * Clears last_pressed list
 */
void Input::clearPresses() {
    last_pressed->clear();
}

/**
 * Checks all the buttons if their state changed
 * from not pressed to pressed since last cycle
 */
void Input::run() {
    if (active) {
        Button *button;
        for (int i = 0; i < buttons->count; i++) {
            button = buttons->get(i);

            button->current = digitalRead(button->pin);

            if (button->current == HIGH && button->last == LOW) {
                addPress(button);
            }

            button->last = button->current;
        }
    }
}