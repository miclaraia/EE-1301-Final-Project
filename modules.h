#include "adafruit.h"

class Module {
public:
    bool active = false;
    MyTimer *timer;
    int id;

    bool check();
    void run();
    void setup();
    void setid();

    static int counter;
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
    int  key_  = 0;

    int left = 0;
    int right = 0;

    void draw(int left, int right);
    void draw(Matrix *matrix, int which);

public:
    Display();
    void setup();
    void run();

    void lock(int address);
    void unlock(int address);
    bool isLocked(int address);

    void setSimon(int lock_address, int state);
    void setTime(int lock_address, int hour, int minute);
    void clearDisplay(int lock_address);
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

class Simon : public Module {
    int disp[R+1];
    int checks[R];
    int rn =1;
    int state = 1;
    //Matrix *matrix;
     //bool rundisp = true;
    // bool Passed = true;
  void setup();

  Input *buttons;
  Display *display;
public : 
Simon();
void setDisplay(Display *display);  
void simondisplay();
void checking();
void fail();
void doButtons();

void setInput(Input *buttoninputs);
static const uint8_t
  topleft_bmp[],
  topright_bmp[], 
  botleft_bmp[], 
  botright_bmp[],
  X_bmp[],
  clean_bmp[];
    
    void run();

};

class Alarm : public Module {
    Display *display;
    Input *input;
    Simon *simon;

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
    void setSimon(Simon *simon);
    void run();
    void setup();

    void setAlarm(int minutes);
    void setAlarm(int hour, int minutes);
    int getAlarm();
};

const uint8_t* getNumericalBitmap(int num);
