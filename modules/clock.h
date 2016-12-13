#ifndef CLOCK_H_
#define CLOCK_H_

/**
 * Module to handle the clock functionality
 */
class Clock : public Module {
    Display *display;

    int hour;
    int minute;

public:
    Clock();
    void run();
    void setup();
    void setDisplay(Display *display);
};

/**
 * Module to handle the alarm functionality
 */
class Alarm : public Module {
    Display *display;
    Input *input;
    Simon *simon;

    int hour;
    int minute;

    int state = 0;
    int flash_count = 0;
    int flash_max = 0;

    bool enabled = true;

    void flash();
    void clear();

public:
    Alarm();
    void setDisplay(Display *display);
    void setInput(Input *input);
    void setSimon(Simon *simon);
    void run();
    void setup();

    void displayAlarm();

    void setAlarm(int minutes);
    void setAlarm(int hour, int minutes);
    int getAlarm();

    void trigger();
    void enable();
    void disable();
};

#endif