#ifndef INPUT_H_
#define INPUT_H_

/**
 * Class to handle all the button inputs
 */
class Input : public Module {
    void initButtons();
public:
    List <Button> *buttons;
    List <int> *last_pressed;

    Input();
    void run();
    void setup();

    void addButton(Button button);
    void clearPresses();
    void addPress(Button *button);

};

#endif