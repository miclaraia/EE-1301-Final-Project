

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

class Simon : public Module {
    int disp[R+1];
    int check[R];
    int rn =1;
    int state = 1;
    Adafruit_BicolorMatrix *matrix;
     //bool rundisp = true;
    // bool Passed = true;
  void setup();

  Input *buttons;

public : 
void display();
void checks();
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
