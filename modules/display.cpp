#include "module.h"
#include "adafruit.h"
#include "display.h"

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
    if (left >= 0) {
        draw(matrix1, left);
    }

    if (right >= 0) {
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

        matrix->drawBitmap(0,0, left_bitmap, 4,8, LED_ON);
        matrix->drawBitmap(4,0, right_bitmap, 4,8, LED_ON);
    }
    
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
    if (!lock_) {
        lock_ = true;
        key_ = address;
    }
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