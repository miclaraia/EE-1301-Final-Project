
class Module {
public:
    bool active = false;
    MyTimer *timer;

    void run();
};

struct Button;
class Input : public Module {
    void initButtons();
public:
    List <Button> *buttons;
    List <int> *last_pressed;

//public:
    Input();

    void addButton(Button button);
    void clearPresses();
    void addPress(Button *button);
    void run();

};

class HeartBeat : public Module {
    bool state = true;
public:
    HeartBeat();
    void run();
};