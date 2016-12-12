#include "adafruit-led-backpack.h"
#include "objects.h"
#include "modules.h"
#include "debug.h"
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

bool Module::check() {
    return active && timer->check();
}

void Module::setid() {
    this->id = counter;
    counter++;
}

Input::Input() {
    setid();
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
    debugButton(button->pin);
    if (button->pin == BUTTON_SNOOZE) {
        debugArray(last_pressed->list, last_pressed->count);
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
    setid();
    setup();
}
void Simon::setinput(Input *buttoninputs){
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
    for(int z = 0; z < rn; z++){
         
       
        //topleft
        if (disp[z] ==1){
            display->setSimon(id,TOPLEFT);
          timer->reset(500);
         continue;
        }
        
        //topright
        if(disp[z] == 2){
          display->setSimon(id,TOPRIGHT);
          timer->reset(500);
          continue;
        }
        
        //botleft
        if(disp[z] == 3){
         display->setSimon(id,BOTTOMLEFT);
          timer->reset(500);
          continue;
        }
        
        //botright
         if (disp[z] == 4) {
         display->setSimon(id,BOTTOMRIGHT);
          timer->reset(500);
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


    state++;
    }
void Simon::fail(){
 
        for(int i=0; i<2; i++){
          display->setSimon(id,TOPRIGHT);
          timer->reset(500);
          display->clearDisplay(id);
          timer->reset(500);
          }
           
           rn = 1;
           state =1;
           }



void Simon::run() {
if(active){

    if(state == DODISPLAY){
    display->lock(id);
    simondisplay();
    state++;}
    if(state == DOBUTTONS){
    doButtons();
    }
    if(state == DOCHECKS){
    checking();
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
    setid();
}
void HeartBeat::run() {
    if (state) digitalWrite(D7, HIGH);
    else digitalWrite(D7, LOW);

    state = !state;
}

// %%%%%%%%%%%% DISPLAY DRIVER



Display::Display() {
    setid();
    setup();
}

void Display::setup() {
    active = true;
    state = 0;
    timer = new MyTimer(250);

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
    draw(left, right);
    // draw(matrix1, state / 5);
    // draw(matrix2, state);

    // state ++;
    // //if (state > 12 && state < 21) state = 21;
    // if (state > 60) state = 0;
}
void Display::draw(int left, int right) {
    if (left > 0) {
        draw(matrix1, left);
    }

    if (right > 0) {
        draw(matrix2, right);
    }

}

void Display::draw(Matrix *matrix, int which) {
    matrix->clear();

    if (which < 100) {
        int right = which % 10;
        int left = which / 10;

        const uint8_t *left_bitmap = getNumericalBitmap(left);
        const uint8_t *right_bitmap = getNumericalBitmap(right);

        if (which > 10)
            matrix->drawBitmap(0,0, left_bitmap, 4,8, LED_ON);
        matrix->drawBitmap(4,0, right_bitmap, 4,8, LED_ON);
    }
    // if (which == 1)
    //     matrix->drawBitmap(4,0, bmp_1, 4,8, LED_ON);
    // else if (which == 2)
    //     matrix->drawBitmap(4,0, bmp_2, 4,8, LED_ON);
    // else if (which == 3)
    //     matrix->drawBitmap(4,0, bmp_3, 4,8, LED_ON);
    // else if (which == 4)
    //     matrix->drawBitmap(4,0, bmp_4, 4,8, LED_ON);
    // else if (which == 5)
    //     matrix->drawBitmap(4,0, bmp_5, 4,8, LED_ON);
    // else if (which == 6)
    //     matrix->drawBitmap(4,0, bmp_6, 4,8, LED_ON);
    // else if (which == 7)
    //     matrix->drawBitmap(4,0, bmp_7, 4,8, LED_ON);
    // else if (which == 8)
    //     matrix->drawBitmap(4,0, bmp_8, 4,8, LED_ON);
    // else if (which == 9)
    //     matrix->drawBitmap(4,0, bmp_9, 4,8, LED_ON);
    // else if (which == 10) {
    //     matrix->drawBitmap(0,0, bmp_1, 4,8, LED_ON);
    //     matrix->drawBitmap(4,0, bmp_0, 4,8, LED_ON);
    // }
    // else if (which == 11){
    //     matrix->drawBitmap(0,0, bmp_1, 4,8, LED_ON);
    //     matrix->drawBitmap(4,0, bmp_1, 4,8, LED_ON);
    // }
    // else if (which == 12){
    //     matrix->drawBitmap(0,0, bmp_1, 4,8, LED_ON);
    //     matrix->drawBitmap(4,0, bmp_2, 4,8, LED_ON);
    //}
    // else if (which > 4 && which < 20) {
    //     matrix->setTextSize(1);
    //     matrix->setTextWrap(false);
    //     matrix->setTextColor(LED_ON);
    //     matrix->setCursor(0,0);
    //     matrix->print(which);
    // }
    else if (which == CLEAR)
        matrix->drawBitmap(0,0, bmp_empty, 8,8, LED_ON);
    else if (which == TOPLEFT) 
        matrix->fillRect(0,0,4,4, LED_ON);
    else if (which == TOPRIGHT)
        matrix->fillRect(4,0,4,4, LED_ON);
    else if (which == BOTTOMLEFT) 
        matrix->fillRect(0,4,4,4, LED_ON);
    else if (which == BOTTOMRIGHT)
        matrix->fillRect(4,4,4,4, LED_ON);
    else if (which == TOP)
        matrix->fillRect(0,0,8,4, LED_ON);
    else if (which == BOTTOM)
        matrix->fillRect(0,4,8,4, LED_ON);
    else if (which == X)
        matrix->drawBitmap(0,0, bmp_x, 8,8, LED_ON);

    matrix->writeDisplay();
}

void Display::setSimon(int lock_address, int state) {
    if (! isLocked(lock_address)) {
        if (state == TOPLEFT) {
            left = TOPLEFT;
            right = CLEAR;
        } else if (state == TOPRIGHT) {
            left = CLEAR;
            right = TOPRIGHT;
        } else if (state == BOTTOMLEFT) {
            left = BOTTOMLEFT;
            right = CLEAR;
        } else if (state == BOTTOMRIGHT) {
            left = CLEAR;
            right = BOTTOMRIGHT;
        } else if (state == X) {
            left = X;
            right = X;
        }
    }
}

void Display::setTime(int lock_address, int hour, int minute) {
    if (! isLocked(lock_address)) {
        left = hour;
        right = minute;
    }
}

void Display::clearDisplay(int lock_address) {
    if (!isLocked(lock_address)) {
        left = CLEAR;
        right = CLEAR;
    }
}

void Display::lock(int address) {
    lock_ = true;
    key_ = address;
}

void Display::unlock(int address) {
    if (key_ == address) {
        lock_ = false;
        key_ = 0;
    }
}

bool Display::isLocked(int address) {
    if (lock_ && address != key_) return true;
    return false;
}

const uint8_t* getNumericalBitmap(int num) {
    switch(num) {
        case 1:
        return bmp_1;

        case 2:
        return bmp_2;

        case 3:
        return bmp_3;

        case 4:
        return bmp_4;

        case 5:
        return bmp_5;

        case 6:
        return bmp_6;

        case 7:
        return bmp_7;

        case 8:
        return bmp_8;

        case 9:
        return bmp_9;

        case 0:
        return bmp_0;
    }

    return bmp_empty;
}

Clock::Clock() {
    setid();
    setup();
}

void Clock::setup() {
    timer = new MyTimer(1000);
}

void Clock::run() {
    // Time.hour() UTC, so in the UK
    // Add 6 hours for time zone difference
    hour = Time.hour() - 6;
    if (hour > 12) hour -= 12;
    minute = Time.minute();

    display->setTime(id, hour, minute);
}

void Clock::setDisplay(Display *display)  {
    this->display = display;
}

Alarm::Alarm() {
    setid();
    setup();
}

void Alarm::setDisplay(Display *display) {
    this->display = display;
}

void Alarm::setInput(Input *input) {
    this->input = input;
}

void Alarm::setSimon(Simon *simon) {
    this->simon = simon;
}

void Alarm::run() {
    List<int> *press = input->last_pressed;
    int pin = *(press->get(press->count - 1));
    if (pin == BUTTON_TOPLEFT) {
        input->clearPresses();
        state = ALARM_FLASH;
        state_count = 0;
    } else if (pin == BUTTON_SNOOZE) {
        input->clearPresses();
        simon->active = true;
        simon->timer->reset();
    }

    if (state == ALARM_FLASH) {
        display->lock(id);
        if (state_count % 2 == 0) flash();
        else clear();

        state_count ++;
        if (state_count > 4) {
            state = ALARM_NORMAL;
            display->unlock(id);
        }
    }

}

void Alarm::setAlarm(int hour, int minutes) {
    this->hour = hour;
    this->minute = minutes;
}

void Alarm::setAlarm(int minutes) {
    this->minute = minutes % 60;
    this->hour = minutes / 60;
}

int Alarm::getAlarm() {
    return hour * 60 + minute;
}

void Alarm::setup() {
    timer = new MyTimer(500);
    hour = 11;
    minute = 11;
}

void Alarm::flash() {
    display->setTime(id, hour, minute);
}

void Alarm::clear() {
    display->clearDisplay(id);
}






