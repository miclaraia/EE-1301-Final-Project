#include "adafruit-led-backpack.h"
#include "objects.h"
#include "modules.h"
//#include "debug.h"

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
    //debugButton(button->pin);
    if (button->pin == BUTTON_SNOOZE) {
        //debugArray(last_pressed->list, last_pressed->count);
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

HeartBeat::HeartBeat() {
    active = true;
    timer = new MyTimer(500);
}
void HeartBeat::run() {
    if (state) digitalWrite(D7, HIGH);
    else digitalWrite(D7, LOW);

    state = !state;
}

// %%%%%%%%%%%% DISPLAY DRIVER
static const uint8_t PROGMEM bmp_top[] =
    { B11111111,
      B11111111,
      B11111111,
      B00000000,
      B00000000,
      B00000000,
      B00000000 };

static const uint8_t PROGMEM bmp_bottom[] =
    { B00000000,
      B00000000,
      B00000000,
      B00000000,
      B11111111,
      B11111111,
      B11111111,
      B11111111 };


Display::Display() {
    setup();
}

void Display::setup() {
    active = true;
    state = 0;
    timer = new MyTimer(500);

    Adafruit_BicolorMatrix *matrix;
    matrix = new Adafruit_BicolorMatrix();
    matrix->begin(0x70);
    matrix1 = matrix;

    matrix = new Adafruit_BicolorMatrix();
    matrix->begin(0x71);
    matrix2 = matrix;
}
void Display::run() {
    if (state == 0) {
        Serial.print("drawing top\n\r");
        matrix2->clear();
        matrix2->drawRect(0,0, 8,8, LED_ON);
        matrix2->fillRect(2,2, 4,4, LED_ON);
        matrix2->writeDisplay();
    } else if (state == 1) {
        Serial.print("drawing bottom\n\r");
        matrix1->clear();
        matrix1->drawBitmap(0, 0, bmp_bottom, 8, 8, LED_ON);
        matrix1->writeDisplay();
    }

    state ++;
    if (state >= 2) state = 0;
}
void Display::draw(int left, int right) {

}
void Display::draw(char *str) {

}
