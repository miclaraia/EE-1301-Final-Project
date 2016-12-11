// This #include statement was automatically added by the Particle IDE.
#include "adafruit-led-backpack/adafruit-led-backpack.h"

/***************************************************
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/


//Notes
//%%%%%%%%%%%%%%%%%%%
/*
buttons:
topleft = D6
top right = D4
bot lef t= D5
bot right = D3
snooze = D2


D0 = IC2 data
D1 = IC2 clock




*/
//%%%%%%%%%%%%%%%%%%%
//Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();
//#define R 5 // r for rounds
// int BUTTON_TOPLEFT = D6;
// int BUTTON_TOPRIGHT = D4;
// int BUTTON_BOTTOMLEFT = D5;
// int BR_ButPIN = D3;
// int SZ_ButPIN = D2;

void setup() {
 // pinMode(BUTTON_TOPLEFT, INPUT_PULLDOWN);
 // pinMode(BUTTON_TOPRIGHT, INPUT_PULLDOWN);
 // pinMode(BUTTON_BOTTOMLEFT, INPUT_PULLDOWN);
 // pinMode(BR_ButPIN, INPUT_PULLDOWN);
 // pinMode(SZ_ButPIN, INPUT_PULLDOWN);
 
 // matrix.setTextWrap(false);
 // matrix.setCursor(0,0);
 //  Serial.begin(9600);
 //  Serial.println("8x8 LED Matrix Test");
 //  matrix.begin(0x70);  // pass in the address
  
 
}

// static const uint8_t
//   topleft_bmp[] =
//   { B11100001,
//     B11100001,
//     B11100001,
//     B11100001,
//     B00000000,
//     B00000000,
//     B00000000,
//     B00000000 },
//   topright_bmp[] =
//   { B00011110,
//     B00011110,
//     B00011110,
//     B00011110,
//     B00000000,
//     B00000000,
//     B00000000,
//     B00000000 },
//   botleft_bmp[] =
//   { B00000000,
//     B00000000,
//     B00000000,
//     B00000000,
//     B11100001,
//     B11100001,
//     B11100001,
//     B11100001 },
//  botright_bmp[] =
//   { B00000000,
//     B00000000,
//     B00000000,
//     B00000000,
//     B00011110,
//     B00011110,
//     B00011110,
//     B00011110 },
//  X_bmp[] =
//   { B00000011,
//     B10000100,
//     B01001000,
//     B00110000,
//     B00110000,
//     B01001000,
//     B10000100,
//     B00000011 },
//  clean_bmp[] =
//   { B11111111,
//     B11111111,
//     B11111111,
//     B11111111,
//     B11111111,
//     B11111111,
//     B11111111,
//     B11111111 };
    
void simon(){
    
    
    // int disp[R+1];
    // int check[R];
    // int rn =1;
    for(int i =0; i<R; i++){
        check[i]=0;
    }
    // will need something different

    // int TL_ButNow;
    // int TR_ButNow;
    // int BL_ButNow;
    // int BR_ButNow;
    // int SZ_ButNow;
    // int TL_ButLast = 0;
    // int TR_ButLast = 0;
    // int BL_ButLast = 0;
    // int BR_ButLast = 0;
    // int SZ_ButLast = 0;
    
    // bool ButOrd[R];
    //     for(int i = 0; i<R;i++){
    //         ButOrd[i] = false;
    //     }

    // bool rundisp = true;
    // //bool TL_Butprs = false;
    // //bool TR_Butprs = false;
    // //bool BL_Butprs = false;
    // //bool BR_Butprs = false;
    // //bool SZ_Butprs = false;
    // bool Passed = true;
    
    
    for (int A =0; A<R; A++){
        
     // sets all the to be used values of disp to a value for it's corrsponding corner   
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(rn ==1){
        for(int j = 0; j< R; j++){
           disp[j] = random(3) + 1;
           //disp[j] = 1;
        }
        disp[R] =0;
         // this is now a call function
    }
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    
    //Did they pass last round?
    if(Passed)
    rundisp = true;
    
    // the display loop
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    if(rundisp)
    for(int z = 0; z < rn; z++){
     
   
    //topleft
    if (disp[z] ==1){
      matrix.clear();
      matrix.drawBitmap(0, 0, topleft_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      delay(500);
      matrix.writeDisplay();
    
      matrix.clear();
      continue;
    }
    
    //topright
    if(disp[z] == 2){
      matrix.clear();
      matrix.drawBitmap(0, 0, topright_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      delay(500);
      matrix.clear();
      matrix.writeDisplay();
      
      continue;
    }
    
    //botleft
    if(disp[z] == 3){
      matrix.clear();
      matrix.drawBitmap(0, 0, botleft_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      delay(500);
      matrix.clear();
      matrix.writeDisplay();
      
      continue;
    }
    
    //botright
     if (disp[z] == 4) {
      matrix.clear();
      matrix.drawBitmap(0, 0, botright_bmp, 8, 8, LED_ON);
      matrix.writeDisplay();
      delay(500);
      matrix.writeDisplay();
      
      matrix.clear();
      continue;
    } 
    else if (rundisp = false);
    //matrix.clear();
    }  // end of display loop
      //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //rn++;
      //Beginning of Person test loop
      //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
      // Note*
      //TL = 1
      //TR = 2
      //BL = 3
      //BR = 4
      // beginning of input loop
      //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    if(Passed)
     for(int i=0; i<rn;) {
           TL_ButNow = digitalRead(BUTTON_TOPLEFT);
        if(TL_ButNow == HIGH && TL_ButLast == LOW) {
        TL_ButLast = HIGH;
        //TL_Butprs = true;
        check[rn-1]=1;
        i++;
        //break;
        }
           TR_ButNow = digitalRead(BUTTON_TOPRIGHT);
        if(TR_ButNow == HIGH && TR_ButLast == LOW) {
        TR_ButLast = HIGH;
        //TR_Butprs = true;
        check[rn-1]=2;
        i++;
        //break;
        }
          BL_ButNow = digitalRead(BUTTON_BOTTOMLEFT);
        if(BL_ButNow == HIGH && BL_ButLast == LOW) {
        BL_ButLast = HIGH;
        //BL_Butprs = true;
        check[rn-1]=3;
        i++;
       // break;
        }
          BR_ButNow = digitalRead(BR_ButPIN);
        if(BR_ButNow == HIGH && BR_ButLast == LOW) {
        BR_ButLast = HIGH;
        //BR_Butprs = true;
        check[rn-1]=4;
        i++;
       // break;
        }
          SZ_ButNow = digitalRead(SZ_ButPIN);
        if(SZ_ButNow == HIGH && SZ_ButLast == LOW) {
        SZ_ButLast = HIGH;
        i++;
        //SZ_Butprs = true;
       // break;
        }
    
     }// end of thumbup (input) loop
      // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
      // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
      // check to see if the correct order, i.e. check loop
    // if(Passed){
    //      for(int i=0; i<rn; i++)
    //         if(check[i] == disp [i])
    //             ButOrd[i] = true;
    //      for(int i=0; i<rn; i++)
    //         if(!ButOrd[i]){
    //             Passed = false;
    //             break;
    //         }
    //         rn++;
    }
       //end of check loop
       //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&     
       //end of Person test loop
       //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
       //beginning of the you failed loop
       //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
       if (!Passed){
        for(int i=0; i<2; i++){
          matrix.clear();
          matrix.drawBitmap(0, 0, X_bmp, 8, 8, LED_ON);
          matrix.writeDisplay();
          delay(500);
          matrix.drawBitmap(0, 0, clean_bmp, 8, 8, LED_OFF);
          matrix.writeDisplay();
          delay(500);
          
          }
           Passed = true;
           rn = 0;
           }
         // End of fail loop
         //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
           
    //<<<<<<< HEAD
           
       
    //=======
           
           
           
       }
    //>>>>>>> d8649f486f8a29e2023d1a9c50aacf1d6e3594c5
       
       
   
} // end of A
 //end of simon

void loop() {
simon();
}
/* matrix.clear();
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();
  matrix.drawBitmap(0, 0, neutral_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();
  matrix.drawBitmap(0, 0, frown_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(500);

  matrix.clear();      // clear display
  matrix.drawPixel(0, 0, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawLine(0,0, 7,7, LED_YELLOW);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawRect(0,0, 8,8, LED_RED);
  matrix.fillRect(2,2, 4,4, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawCircle(3,3, 3, LED_YELLOW);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextSize(1);
  matrix.setTextColor(LED_ON);
  for (int8_t x=7; x>=-36; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Hello");
    matrix.writeDisplay();
    delay(100);
  }
  matrix.setRotation(3);
  matrix.setTextColor(LED_RED);
  for (int8_t x=7; x>=-36; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("World");
    matrix.writeDisplay();
    delay(100);
  }
  matrix.setRotation(0);
  
  
  
  
  
  
  
  
  
int ButtonPIN = D2;
int PotPIN = A2;
int PotOut = 0;
int ButtonNow;
int ButtonLast = 0;
bool ButtonOut = FALSE;
int ButtonCount = 0;
void setup() {
 pinMode(ButtonPIN, INPUT_PULLDOWN);
 pinMode(PotPIN, INPUT);
 Serial.begin(9600);
}
void loop() {
  ButtonNow = digitalRead(ButtonPIN);
if(ButtonNow == HIGH && ButtonLast == LOW) {
ButtonLast = HIGH;
PotOut = analogRead(PotPIN);
 if(ButtonLast == HIGH) {
 ButtonCount = ButtonCount + 1;
 Serial.print("Button Count = ");
 Serial.print(ButtonCount);
 Serial.print(" , Level = ");
 Serial.println(PotOut);
 }

} else if (ButtonNow == LOW) {
ButtonLast = LOW;
}  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
}*/