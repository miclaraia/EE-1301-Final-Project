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

#endif