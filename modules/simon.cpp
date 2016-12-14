#include "module.h"
#include "input.h"
#include "display.h"
#include "light.h"
#include "simon.h"

/////////////////////////////////////////////////////
// in this comment chunk we have the setup of simon
// all parts here are what are necessary to setup the 
// module as well as allow it to interact with others
Simon::Simon(){
    timer = new MyTimer(175);
    setup();
}
void Simon::setInput(Input *buttoninputs){
    buttons = buttoninputs;
}
void Simon::setDisplay(Display *display){
    this->display = display;
}
void Simon::setLight(Light *light){
  this->light = light;
}
void Simon::setup(){
  // this loop assigns 1 of four values, each value 
  // corresponding to a respective corner
    for(int j = 0; j< R; j++){
           disp[j] = random(3) + 1;
           checks[j] = 0;              // just to clear it
        }
        state = 1;                     // state of the run function
        rn = 1;                        // Round number
        tempstate =1;                  // state variable within the smaller parts
        failed = false;                // can't fail instantly
        z =0;                          // temp variable to be used in smaller parts

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// This is the display function for simon, this is what 
// will show the respective corners
void Simon::simondisplay(){
     ////////////////////////////////////////
      // here we have the function that will progress to the next stage 
      // of simon
       if(z >= rn){
    display->clearDisplay(id);
    buttons->clearPresses();
    z = 0;
    state = DOBUTTONS;

  }

  if(tempstate >= 2){
      tempstate++;
      if(tempstate >= 5) // this number difference allows for a period
          tempstate = 1; // of time to remain on, albeit a small time

      display->clearDisplay(id);
    
    }
    
// fairly self-explanatory here
   
 if (tempstate <= 1){
    ///////////////////////////////////
    //topleft
    if (disp[z] ==1){
        
     display->setSimon(id,TOPLEFT); 
     tempstate = 2;    
    }

    ///////////////////////////////////
    //topright
    if(disp[z] == 2){
        
      display->setSimon(id,TOPRIGHT);
      tempstate = 2;
    }

    ///////////////////////////////////
    //botleft
    if(disp[z] == 3){
        
     display->setSimon(id,BOTTOMLEFT);
      tempstate = 2;
    }

    ///////////////////////////////////
    //botright
     if (disp[z] == 4) {
        
     display->setSimon(id,BOTTOMRIGHT);
      tempstate = 2;      
    }
    z++; // temp variable to keep track of which round's disp we're on
  }
   
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// allows for down time for the user to press the correct corresponding buttons
void Simon::doButtons() {

    if (rn == buttons->last_pressed->count)
        state++;
    
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Checking function to see if the button order of those pressed is right
void Simon::checking(){
  // this for loop here is the method by which the interaction between
  // simon and the interaction of the button presses is translated to 
  // allow for a cross check between the disp array (the array saying 
  // which corner to be), and the check array (holds the value of what
  // buttons were pressed)
  // this is necessary due to the different values having been assigned
  // in different parts of the code

  for(int i =0; i<rn; i++){
      if(buttons->last_pressed->list[i] == BUTTON_TOPLEFT)
          checks[i] = SIMONTOPLEFT;
      else if(buttons->last_pressed->list[i] == BUTTON_TOPRIGHT)
          checks[i] = SIMONTOPRIGHT;
      else if(buttons->last_pressed->list[i] == BUTTON_BOTTOMLEFT)
          checks[i] = SIMONBOTTOMLEFT;
      else if(buttons->last_pressed->list[i] == BUTTON_BOTTOMRIGHT)
          checks[i] = SIMONBOTTOMRIGHT;
      else state = 1; // if some error, a just in case

     
  }
  
  for (int i =0; i<rn; i++)
        if(disp[i] != checks[i]){
                                                  // if any of the button presses don't match, they have failed
            failed = true;
            break;
           }
      if(failed)                                  // sets the state of the whole simon to having failed
        state = FAILED;
      if(!failed){                                // if they didn't fail
         if(rn == R && state != DODISPLAY){
             state = PASSED;                      // if it's last round, they've won
         }
         else {                                   // if it isn't last round, to next round we go
           rn++;
           state =DODISPLAY;
         }
      }
          
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void Simon::fail(){

  if(z <= 6) {                          // 6 just being a number allowing for the x to flash multiple times,
    z++;                                // change 6 to a higher number, fewer flashes

         if (tempstate >= 2){
         display->clearDisplay(id);

         tempstate = 1;
       }
                                        // we just switch between the two different states within the func
                                        // to flash the x and flash blank

         if (tempstate <= 1){
         display->setSimon(id,X);
        
         tempstate++;
        
       }


          }
      else {
      light->brighter();                  // cause the light to get brighter, thus more obnoxious
      setup();                            // Could put brighter elsewhere, but for simplicity, make it a consequence
                                          // to reset the values of simon's displays
       
         }
}
 

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// The guts of the function, what get's called by main, some functions self-explanatory
void Simon::run() {
if(active){

    if(state == DODISPLAY){
    display->lock(id);                        // so simon has control of the display
      simondisplay();
  }
    if(state == DOBUTTONS){
      doButtons();
    }
    if(state == DOCHECKS){
      checking();
    }
    if(state == PASSED){
      
      light->disable();                       //turn off the light, you did it!
      buttons->clearPresses();                // so button presses are accurate outside of simon
      active = false;                         // turn simon off, only way to do it, is to pass
      display->unlock(id);                    // give back control of the display
    }
    if(state == FAILED){
    fail();
    }

}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// to allow simon to be played outside of the web functionality
void Simon::play() {
  active = true;
  setup();
  buttons->clearPresses();
  timer->reset();
  light->brighter();
}