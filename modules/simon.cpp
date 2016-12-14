#include "module.h"
#include "input.h"
#include "display.h"
#include "simon.h"

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
void Simon::setup(){
    for(int j = 0; j< R; j++){
           disp[j] = random(3) + 1;
           checks[j] = 0; // just to clear it
        }
        state = 1;
        rn = 1;
        tempstate =1;
        failed = false;
        z =0; // just in case

}
void Simon::simondisplay(){
     // for(int z = 0; z < rn; z++){

       Serial.print("t; ");
       Serial.print(tempstate);
       Serial.print("\n\r");
       if(z >= rn){
        display->clearDisplay(id);
        buttons->clearPresses();
        z = 0;
        state = DOBUTTONS;

      }

      if(tempstate >= 2){
          tempstate++;
        if(tempstate >= 5)
          tempstate = 1;
        

        display->clearDisplay(id);
        
        }
        

       
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
        z++;
      }
   
}

void Simon::doButtons() {

    if (rn == buttons->last_pressed->count){
      Serial.print(buttons->last_pressed->list[0]);
        state++;
        //buttons->last_pressed->list[]
    }

}
void Simon::checking(){
    for(int i =0; i<rn; i++){
        if(buttons->last_pressed->list[i] == BUTTON_TOPLEFT)
            checks[i] = SIMONTOPLEFT;
        else if(buttons->last_pressed->list[i] == BUTTON_TOPRIGHT)
            checks[i] = SIMONTOPRIGHT;
        else if(buttons->last_pressed->list[i] == BUTTON_BOTTOMLEFT)
            checks[i] = SIMONBOTTOMLEFT;
        else if(buttons->last_pressed->list[i] == BUTTON_BOTTOMRIGHT)
            checks[i] = SIMONBOTTOMRIGHT;
        else state = 1; // if some error

        String d = String(disp[i]);
            String c = String(checks[i]);
            String c1 = String(i);
            String c2 = String(rn);
            Serial.print("i: " + c1 + " rn: " + c2 + " disp: " + d + " check: " + c + "\n\r");
    }
    
        for (int i =0; i<rn; i++)
          if(disp[i] != checks[i]){
            String d = String(disp[i]);
            String c = String(checks[i]);
            Serial.print("disp: " + d + "check: " + c + "\n\r");
              //fail();
              failed = true;
             }
        if(failed)
          state = FAILED;
        if(!failed){
        if(rn == R && state != DODISPLAY){
            state = PASSED;
        }else {
          rn++;
          state =DODISPLAY;}
      }
        
         


        /*if(state != 1){
            rn++;
            state = DODISPLAY;
        }*/
       
    
    }
void Simon::fail(){
      if(z <= 6) {// 4 being double the number of times x flashes
        z++;

             if (tempstate >= 2){
             display->clearDisplay(id);
             
             tempstate = 1;
           }

             if (tempstate <= 1){
             display->setSimon(id,X);
            
             tempstate++;
            
           }


              }
          else setup();// to reset the values of simon's displays
           
         
}
 
        // for(int i=0; i<2; i++){
        //   display->setSimon(id,X);
        //   
        //   //display->clearDisplay(id);
        //   
        //   }
           
        //    rn = 1;
        //    state = DODISPLAY;
        //    }



void Simon::run() {
if(active){

    if(state == DODISPLAY){
    display->lock(id);
    simondisplay();
  }
    if(state == DOBUTTONS){
    doButtons();
    }
    if(state == DOCHECKS){
    checking();
    }
    if(state == PASSED){
      buttons->clearPresses();
        active = false;
        display->unlock(id);
    }
    if(state == FAILED){
    fail();
    }

}
}

void Simon::play() {
  active = true;
  

  setup();

  buttons->clearPresses();
  timer->reset();
}