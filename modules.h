
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

class Spearker : public Module {

}

class Display : public Module {
    
}