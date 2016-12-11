#include "objects.h"
#include "definitions.h"

Input::Input() {
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
    buttons[count] = button;
    count++;
}

void Input::addPress(Button *button) {
    if (last_pressed_count + 1 >= LAST_PRESSED_LENGTH) {
        // TODO shift array left by 1
        // drop leftmost element
        // decrement count
    }

    last_pressed[last_pressed_count] = button->pin;
    last_pressed_count++;
}

Input::run() {
    if (active) {
        Button *button;
        for (int i = 0; i < count; i++) {
            button = *buttons[i];
            button->current = digitalRead(BUTTON);
            if (button->current == HIGH && button->last == LOW) {
                
            
            selectRate(blinkState);
        }
    }
}