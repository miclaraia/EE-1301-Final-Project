#include "module.h"
#include "input.h"
#include "display.h"
#include "simon.h"
#include "clock.h"
#include "definitions.h"

Clock::Clock() {
    setup();
}

void Clock::setup() {
    timer = new MyTimer(1000);
}

void Clock::run() {
    // Time.hour() UTC, so in the UK
    // Add 6 hours for time zone difference
    hour = Time.hour() - 6;
    if (hour > 12) hour -= 12;
    minute = Time.minute();

    display->setTime(id, hour, minute);
}

void Clock::setDisplay(Display *display)  {
    this->display = display;
}

Alarm::Alarm() {
    setup();
}

void Alarm::setDisplay(Display *display) {
    this->display = display;
}

void Alarm::setInput(Input *input) {
    this->input = input;
}

void Alarm::setSimon(Simon *simon) {
    this->simon = simon;
}

void Alarm::run() {
    if (!simon->active) {
        List<int> *press = input->last_pressed;
        int pin = *(press->get(press->count - 1));
        if (pin == BUTTON_TOPLEFT) {
            input->clearPresses();
            displayAlarm();
        } 

        else if (pin == BUTTON_SNOOZE) {
            input->clearPresses();
            simon->active = true;
            simon->timer->reset();
        }

        if (state == ALARM_FLASH) {
            display->lock(id);
            if (state_count % 2 == 0) flash();
            else clear();

            state_count ++;
            if (state_count > 4) {
                state = ALARM_NORMAL;
                display->unlock(id);
            }
        }
    }

}

void Alarm::displayAlarm() {
    state = ALARM_FLASH;
    state_count = 0;

}

void Alarm::setAlarm(int hour, int minutes) {
    this->hour = hour;
    this->minute = minutes;
}

void Alarm::setAlarm(int minutes) {
    this->minute = minutes % 60;
    this->hour = minutes / 60;
}

int Alarm::getAlarm() {
    return hour * 60 + minute;
}

void Alarm::setup() {
    timer = new MyTimer(500);
    hour = 11;
    minute = 11;
}

void Alarm::flash() {
    display->setTime(id, hour, minute);
}

void Alarm::clear() {
    display->clearDisplay(id);
}