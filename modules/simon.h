#ifndef SIMON_H_
#define SIMON_H_s

/**
 * Module to play the simon-says game
 */
class Simon : public Module {
    int disp[R+1];
    int checks[R];
    int rn =1;
    int state = 1;
    
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

    void play();

    void setInput(Input *buttoninputs);
    void run();

};

#endif