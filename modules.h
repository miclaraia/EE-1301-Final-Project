#ifdef MODULE_H_
#define MODULE_H_

class Module {
public:
    bool active = false;
    MyTimer *timer;

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
    Adafruit_BicolorMatrix *matrix1;
    Adafruit_BicolorMatrix *matrix2;
    int state = 0;

public:
    Display();
    void setup();
    void run();
    void draw(int left, int right);
    void draw(char *str);
};

#endif