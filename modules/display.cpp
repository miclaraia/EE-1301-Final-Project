#include "module.h"
#include "adafruit.h"
#include "display.h"

Display::Display() {
    setup();
}

/**
 * Initialize variables and matrix
 */
void Display::setup() {
    // Make active
    active = true;
    // Create timer
    timer = new MyTimer(100);

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

/**
 * Draw the image currently set to left and right variable
 */
void Display::run() {
    draw(left, right);
}

/**
 * Draw the requested images
 */ 
void Display::draw(int left, int right) {
    if (left >= 0) {
        draw(matrix1, left);
    }

    if (right >= 0) {
        draw(matrix2, right);
    }

}

/**
 * Draw the rqeuested image to this matrix
 */
void Display::draw(Matrix *matrix, int which) {
    matrix->clear();

    // Numbers are 0 - 100, and other special bitmaps have
    // reference numbers > 100
    if (which < 100) {

        // Split number into respective digits
        int right = which % 10;
        int left = which / 10;

        // Get reference to the bitmaps
        const uint8_t *left_bitmap = getNumericalBitmap(left);
        const uint8_t *right_bitmap = getNumericalBitmap(right);

        // Draw each digit on the matrix
        // Right digit is offset by 4
        // Each digit has width of 3, so there should
        // be a 1 col gap between them
        matrix->drawBitmap(0,0, left_bitmap, 4,8, LED_ON);
        matrix->drawBitmap(4,0, right_bitmap, 4,8, LED_ON);
    }
    
    // Not a digit, draw the bitmap on the whole width of the matrix
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

/**
 * Convenience method so simon can draw its images
 */
void Display::setSimon(int lock_id, int state) {
    if (! isLocked(lock_id)) {
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

/**
 * Convenience method so the clock and alarm can draw a time
 * easily.
 */
void Display::setTime(int lock_id, int hour, int minute) {
    if (! isLocked(lock_id)) {
        left = hour;
        right = minute;
    }
}

/**
 * Empty the screen
 */
void Display::clearDisplay(int lock_id) {
    if (!isLocked(lock_id)) {
        left = CLEAR;
        right = CLEAR;
    }
}

/**
 * Lock the screen
 */
void Display::lock(int id) {
    if (!lock_) {
        lock_ = true;
        key_ = id;
    }
}

/**
 * Unlock the screen
 */
void Display::unlock(int id) {
    if (key_ == id) {
        lock_ = false;
        key_ = 0;
    }
}

/**
 * Check if the module with this id can
 * use the display
 */
bool Display::isLocked(int id) {
    if (lock_ && id != key_) return true;
    return false;
}

/**
 * Force the display to unlock. Only used for overriding purposes,
 * never use this for regular locking/unlocking
 */
void Display::forceUnlock() {
    lock_ = false;
}

/**
 * Method to get a pointer to a bitmap from memory
 */
const uint8_t* getNumericalBitmap(int bitmap) {
    switch(bitmap) {
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