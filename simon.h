class Simon : public Module {
	int disp[R+1];
    int checks[R];
    int rn =1;
    Adafruit_BicolorMatrix *matrix;
     //bool rundisp = true;
    // bool Passed = true;
  void setup();

  Input *buttons;

public : 
void disp();
void checking();
void fail();
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

}
