#include "adafruit-led-backpack.h"
#include "objects.h"
#include "modules.h"
//#include "debug.h"
static const uint8_t
  topleft_bmp[] =
  { B11100001,
    B11100001,
    B11100001,
    B11100001,
    B00000000,
    B00000000,
    B00000000,
    B00000000 },
  topright_bmp[] =
  { B00011110,
    B00011110,
    B00011110,
    B00011110,
    B00000000,
    B00000000,
    B00000000,
    B00000000 },
  botleft_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11100001,
    B11100001,
    B11100001,
    B11100001 },
 botright_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011110,
    B00011110,
    B00011110,
    B00011110 },
 X_bmp[] =
  { B00000011,
    B10000100,
    B01001000,
    B00110000,
    B00110000,
    B01001000,
    B10000100,
    B00000011 },
 clean_bmp[] =
  { B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111,
    B11111111 };

template<class T>
List<T>::List(int length) {
    this->max = length;
    list = new T[length];
}

template<class T>
void List<T>::add(T t) {
    if (count < max) {
        list[count] = t;
        count++;
    }
}

template<class T>
void List<T>::clear() {
    count = 0;
}

template<class T>
T * List<T>::get(int index) {
    return &list[index];
}

Input::Input() {
    setup();
}

void Input::setup() {
    buttons = new List<Button>(10);
    last_pressed = new List<int>(LAST_PRESSED_LENGTH);

    timer = new MyTimer(100);
    Button button;

    button.pin = BUTTON_TOPLEFT;
    addButton(button);

    button.pin = BUTTON_TOPRIGHT;
    addButton(button);

    button.pin = BUTTON_BOTTOMRIGHT;
    addButton(button);

    button.pin = BUTTON_BOTTOMLEFT;
    addButton(button);

    button.pin = BUTTON_SNOOZE;
    addButton(button);

    initButtons();
}

void Input::initButtons() {
    for (int i = 0; i < buttons->count; i++) {
        int pin = buttons->get(i)->pin;
        pinMode(pin, INPUT_PULLDOWN);
    }
}

void Input::addButton(Button button) {
    buttons->add(button);
}

void Input::addPress(Button *button) {
    //debugButton(button->pin);
    if (button->pin == BUTTON_SNOOZE) {
        //debugArray(last_pressed->list, last_pressed->count);
        last_pressed->clear();
    }


    if (last_pressed->count + 1 >= last_pressed->max) {
        for (int i = 1; i < last_pressed->count; i++) {
            last_pressed->list[i - 1] = last_pressed->list[i];
        }
        last_pressed->count--;
    }

    last_pressed->list[last_pressed->count] = button->pin;
    last_pressed->count++;
}

void Input::clearPresses() {
    last_pressed->clear();
}

void Input::run() {
    if (active) {
        Button *button;
        for (int i = 0; i < buttons->count; i++) {
            button = buttons->get(i);

            button->current = digitalRead(button->pin);

            if (button->current == HIGH && button->last == LOW) {
                //std::stringstream ss;
                //ss << "i: " << i;
                //debug(&ss);
                addPress(button);
            }

            button->last = button->current;
        }
    }
}



//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Jaydon's shit
Simon::Simon(){
    timer = new MyTimer(100);

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
        

    matrix =  new Adafruit_8x8matrix();
    matrix->setTextWrap(false);
    matrix->setCursor(0,0);
    matrix->begin(0x70);
    setup();
}
void Simon::setinput(Input *buttoninputs){
    buttons = buttoninputs;

}
void Simon::setup(){
    for(int j = 0; j< R; j++){
           disp[j] = random(3) + 1;
           //disp[j] = 1;
        }
        disp[R] =0;

}
void Simon::display(){
    for(int z = 0; z < rn; z++){
         
       
        //topleft
        if (disp[z] ==1){
          matrix->clear();
          matrix->drawBitmap(0, 0, topleft_bmp, 8, 8, LED_ON);
          matrix->writeDisplay();
          timer->reset(500);
          //matrix->writeDisplay();
        
          //matrix->clear();
          continue;
        }
        
        //topright
        if(disp[z] == 2){
          matrix->clear();
          matrix->drawBitmap(0, 0, topright_bmp, 8, 8, LED_ON);
          matrix->writeDisplay();
          timer->reset(500);
          //matrix->clear();
          //matrix->writeDisplay();
          
          continue;
        }
        
        //botleft
        if(disp[z] == 3){
          matrix->clear();
          matrix->drawBitmap(0, 0, botleft_bmp, 8, 8, LED_ON);
          matrix->writeDisplay();
          timer->reset(500);
          //matrix->clear();
          //matrix->writeDisplay();
        
          continue;
        }
        
        //botright
         if (disp[z] == 4) {
          matrix->clear();
          matrix->drawBitmap(0, 0, botright_bmp, 8, 8, LED_ON);
          matrix->writeDisplay();
          timer->reset(500);
          //matrix->writeDisplay();
          
          //matrix->clear();
          continue;
        } 
        

    }
}
void Simon::doButtons() {
    if (rn == buttons->last_pressed->count){
        state++;
        //buttons->last_pressed->list[]
    }

}
void Simon::checks(){
    for(int i =0; i<rn; i++){
        if(buttons->last_pressed->list[i] == BUTTON_TOPLEFT)
            check[i] = TOPLEFT;
        else if(buttons->last_pressed->list[i] == BUTTON_TOPRIGHT)
            check[i] = TOPRIGHT;
        else if(buttons->last_pressed->list[i] == BUTTON_BOTTOMLEFT)
            check[i] = BOTTOMLEFT;
        else if(buttons->last_pressed->list[i] == BUTTON_BOTTOMRIGHT)
            check[i] = BOTTOMRIGHT;
        else state = 1;
    }
    for (int i =0; i<rn; i++)
        if(disp[i] != check[i])
            fail();


    state++;
    }
void Simon::fail(){
 
        for(int i=0; i<2; i++){
          matrix->clear();
          matrix->drawBitmap(0, 0, X_bmp, 8, 8, LED_ON);
          matrix->writeDisplay();
          delay(500);
          matrix->drawBitmap(0, 0, clean_bmp, 8, 8, LED_OFF);
          matrix->writeDisplay();
          delay(500);
          
          }
           
           rn = 1;
           state =1;
           }



void Simon::run() {
if(active){
    if(state == DODISPLAY){
    display();
    state++;}
    if(state == DOBUTTONS){
    doButtons();
    }
    if(state == DOCHECKS){
    checks();
    }
    if(state == PASSED){
        active = false;
    }
}




}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% end Jaydon's shit

HeartBeat::HeartBeat() {
    active = true;
    timer = new MyTimer(500);
}
void HeartBeat::run() {
    if (state) digitalWrite(D7, HIGH);
    else digitalWrite(D7, LOW);

    state = !state;
}

// %%%%%%%%%%%% DISPLAY DRIVER



Display::Display() {
    setup();
}

void Display::setup() {
    active = true;
    state = 0;
    timer = new MyTimer(1000);

    Matrix *matrix;
    matrix = new Adafruit_8x8matrix();
    matrix->begin(0x71);
    matrix->setRotation(1);
    matrix1 = matrix;

    matrix = new Adafruit_8x8matrix();
    matrix->begin(0x70);
    matrix->setRotation(1);
    matrix2 = matrix;
}
void Display::run() {
    if (state == 0) {
        Serial.print("drawing top\n\r");
        draw(matrix1, TOPLEFT);

    } else if (state == 1) {
        Serial.print("drawing bottom\n\r");
        draw(matrix1, TOPRIGHT);

    }

    state ++;
    if (state >= 2) state = 0;
}
void Display::draw(int left, int right) {
    if (left > 0) {
        draw(matrix1, left);
    }

    if (right > 0) {

    }

}

void Display::draw(Matrix *matrix, int which) {
    matrix->clear();
    if (which < 20)
        matrix->print(which);
    else if (which == TOPLEFT) 
        matrix->fillRect(0,0,4,4, LED_ON);
    else if (which == TOPRIGHT)
        matrix->fillRect(4,0,4,4, LED_ON);

    matrix->writeDisplay();
}
