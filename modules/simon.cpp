#include "module.h"
#include "input.h"
#include "display.h"
#include "simon.h"

Simon::Simon(){
    timer = new MyTimer(500);
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
           //disp[j] = 1;
        }
        disp[R] =0;

}
void Simon::simondisplay(){
     // for(int z = 0; z < rn; z++){
       Serial.print("t; ");
       Serial.print(tempstate);
       Serial.print("\n\r");
       if(z >= rn){
        display->clearDisplay(id);
        state++;
      }

      if(tempstate > 1){

        if(tempstate > 2)
          tempstate = 0;
          else tempstate++;

        display->clearDisplay(id);
        z++;
        }
        

       
     if (tempstate <= 1){
        ///////////////////////////////////
        //topleft
        if (disp[z] ==1){
            
         display->setSimon(id,TOPLEFT);

         tempstate++;    
    
        }
        ///////////////////////////////////
        //topright
        if(disp[z] == 2){
            
          display->setSimon(id,TOPRIGHT);
          
          tempstate++;
        }
        ///////////////////////////////////
        //botleft
        if(disp[z] == 3){
            
         display->setSimon(id,BOTTOMLEFT);
          
          tempstate++;
  
        }
        ///////////////////////////////////
        //botright
         if (disp[z] == 4) {
            
         display->setSimon(id,BOTTOMRIGHT);
           
          tempstate++;      
    
        }
      }
   
}
//     for(int z = 0; z < rn; z++){
         
       
//         //topleft
//         if (disp[z] ==1){
//             display->setSimon(id,TOPLEFT);
//           
//           //display->clearDisplay(id);
//           //
//          continue;
//         }
        
//         //topright
//         if(disp[z] == 2){
//           display->setSimon(id,TOPRIGHT);
//           
//          // display->clearDisplay(id);
//           //
//           continue;
//         }
        
//         //botleft
//         if(disp[z] == 3){
//          display->setSimon(id,BOTTOMLEFT);
//           
//           //display->clearDisplay(id);
//           //
//           continue;
//         }
        
//         //botright
//          if (disp[z] == 4) {
//          display->setSimon(id,BOTTOMRIGHT);
//           
//          // display->clearDisplay(id);
//           //
//           continue;
//         } 
        

//     }
// }
void Simon::doButtons() {
    if (rn == buttons->last_pressed->count){
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
        else state = 1;
    }
    
    for (int i =0; i<rn; i++)
        if(disp[i] != checks[i])
            fail();
        if(rn == R && state != DODISPLAY){
            state = PASSED;
        }
        if(state != 1){
            rn++;
            state = DODISPLAY;
        }
       




    
    }
void Simon::fail(){
 
 for(int i=0; i<2; i++){
        if (tempstate == 1){
          display->setSimon(id,X);
          
          tempstate++;
          i--; // same reason as the z-- before
            }
        if (tempstate == 2){
          display->clearDisplay(id);
          
          tempstate--;
          }
           }
           rn = 1; // back to round one
           state = DODISPLAY; // have to reset state
           setup();// to reset the values of simon's displays
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
    //state++;
  }
    if(state == DOBUTTONS){
    doButtons();
    }
    if(state == DOCHECKS){
    checking();
    }
    if(state == PASSED){
        active = false;
        display->unlock(id);
    }
}
}

void Simon::play() {
  active = true;
  state = 1;
  rn = 1;

  setup();

  buttons->clearPresses();
  timer->reset();
}