#ifndef DISPLAY_H_
#define DISPLAY_H_

class Display : public Module {
    Matrix *matrix1;
    Matrix *matrix2;
    int state = 0;

    bool lock_ = false;
    int  key_  = 0;

    int left = 0;
    int right = 0;

    void draw(int left, int right);
    void draw(Matrix *matrix, int which);

public:
    Display();
    void setup();
    void run();

    void lock(int address);
    void unlock(int address);
    bool isLocked(int address);

    void setSimon(int lock_address, int state);
    void setTime(int lock_address, int hour, int minute);
    void clearDisplay(int lock_address);
};

const uint8_t* getNumericalBitmap(int num);

#endif