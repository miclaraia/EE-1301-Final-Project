#ifndef SIMON_H_
#define SIMON_H_

#include "light.h"

/**
 * Module to play the simon-says game
 */
class Simon : public Module {
    int disp[R];          // The Display array, delegating which corner will be displayed
    int checks[R];          // Check array, used to check if button order is correct
    int rn = 1;             // Round Number
    int state = 1;          // State of Simon
    int tempstate =1;       // Temporary, or inter-simon, state
    int z =0;               // Temp, incremental variable
    bool failed = false;
    
    void setup();

    Input *buttons;
    Display *display;
    Light *light;

public : 
    Simon();
    void setDisplay(Display *display); 
    void setLight(Light *light); 
    void simondisplay();
    void checking();
    void fail();
    void doButtons();

    void play();

    void setInput(Input *buttoninputs);
    void run();

};

#endif