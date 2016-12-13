#include "module.h"
#include "input.h"
#include "display.h"
#include "simon.h"
#include "clock.h"
#include "definitions.h"

Clock::Clock() {
    setup();
}

// Create timer
void Clock::setup() {
    timer = new MyTimer(1000);
}

/**
 * Get current time and send it to teh display
 */
void Clock::run() {
    // Time.hour() UTC, so in the UK
    // Add 6 hours for time zone difference
    hour = Time.hour() - 6;
    if (hour > 12) hour -= 12;
    minute = Time.minute();

    display->setTime(id, hour, minute);
}

/**
 * Set pointer to display module
 */
void Clock::setDisplay(Display *display)  {
    this->display = display;
}

Alarm::Alarm() {
    setup();
}

/**
 * Set pointer to display module
 */
void Alarm::setDisplay(Display *display) {
    this->display = display;
}

/**
 * Set pointer to input module
 */
void Alarm::setInput(Input *input) {
    this->input = input;
}

/**
 * Set pointer to display module
 */
void Alarm::setSimon(Simon *simon) {
    this->simon = simon;
}

/**
 * Checks for relevant button presses, like snooze button,
 * Alarm display button, etc. Can be put in mode where
 * it takes control of display and flashes alarm time
 *
 * Doesn't do anything if simon is running (aka active)
 */
void Alarm::run() {
    if (!simon->active) {

        // Get most recent button press
        List<int> *press = input->last_pressed;
        int pin = *(press->get(press->count - 1));

        /**
         * When in clock mode, pressing top-left button
         * causes current alarm set time to flash
         */
        if (pin == BUTTON_TOPLEFT) {
            input->clearPresses();
            displayAlarm();
        } 

        /**
         * Currently, pressing snooze button 
         * activates simon says game
         */
        else if (pin == BUTTON_SNOOZE) {
            input->clearPresses();
            simon->active = true;
            simon->timer->reset();
        }

        /**
         * Take control of display and flash the alarm time
         */
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

/**
 * Enter mode to flash the alarm
 */
void Alarm::displayAlarm() {
    state = ALARM_FLASH;
    state_count = 0;

}

/**
 * Set the time of the alarm
 */
void Alarm::setAlarm(int hour, int minutes) {
    this->hour = hour;
    this->minute = minutes;
}

/**
 * Set the time of the alarm, accepts time
 * as sum of minutes (eg 120 minutes = 2 hours)
 */
void Alarm::setAlarm(int minutes) {
    this->minute = minutes % 60;
    this->hour = minutes / 60;
}

/**
 * Returns the current alarm time as sum of minutes
 */
int Alarm::getAlarm() {
    return hour * 60 + minute;
}

/**
 * Initialize alarm time
 */
void Alarm::setup() {
    timer = new MyTimer(500);
    hour = 11;
    minute = 11;
}

/**
 * Tell display to show current time
 */
void Alarm::flash() {
    display->setTime(id, hour, minute);
}

/**
 * Tell display to clear both screens
 */
void Alarm::clear() {
    display->clearDisplay(id);
}