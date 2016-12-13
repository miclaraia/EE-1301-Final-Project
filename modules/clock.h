#ifndef CLOCK_H_
#define CLOCK_H_

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

class Alarm : public Module {
    Display *display;
    Input *input;
    Simon *simon;

    int hour;
    int minute;

    int state = 0;
    int state_count = 0;

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
};

#endif