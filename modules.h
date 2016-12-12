#include "adafruit.h"

class Module {
public:
    bool active = false;
    MyTimer *timer;

    bool check();
    void run();
    void setup();
};

struct Button;
class Input : public Module {
    void initButtons();
public:
    List <Button> *buttons;
    List <int> *last_pressed;

//public:
    Input();
    void run();
    void setup();

    void addButton(Button button);
    void clearPresses();
    void addPress(Button *button);

};

class Simon : public Module {
    int disp[R+1];
    int checks[R];
    int rn =1;
    int state = 1;
    Matrix *matrix;
     //bool rundisp = true;
    // bool Passed = true;
  void setup();

  Input *buttons;

public : 
void display();
void checking();
void fail();
void doButtons();
Simon();
void setinput(Input *buttoninputs);
static const uint8_t
  topleft_bmp[],
  topright_bmp[], 
  botleft_bmp[], 
  botright_bmp[],
  X_bmp[],
  clean_bmp[];
    
    void run();

};

class HeartBeat : public Module {
    bool state = true;
public:
    HeartBeat();
    void run();
};

class Speaker : public Module {

};

class Display : public Module {
    Matrix *matrix1;
    Matrix *matrix2;
    int state = 0;

    bool lock_ = false;
    size_t  key_  = 0;

    int left = 0;
    int right = 0;

    void draw(int left, int right);
    void draw(Matrix *matrix, int which);

public:
    Display();
    void setup();
    void run();

    void lock(size_t address);
    void unlock(size_t address);
    bool isLocked(size_t address);

    void setSimon(size_t lock_address, int state);
    void setTime(size_t lock_address, int hour, int minute);
    void clearDisplay(size_t lock_address);
};

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

    int hour;
    int minute;

    int state = ALARM_NORMAL;
    int state_count = 0;

    void flash();
    void clear();

public:
    Alarm();
    void setDisplay(Display *display);
    void setInput(Input *input);
    void run();
    void setup();

    void setAlarm(int minutes);
    void setAlarm(int hour, int minutes);
    int getAlarm();
};

const uint8_t* getNumericalBitmap(int num);
