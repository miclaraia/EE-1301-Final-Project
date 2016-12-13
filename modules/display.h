#ifndef DISPLAY_H_
#define DISPLAY_H_

class Display : public Module {
    Matrix *matrix1;
    Matrix *matrix2;

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

    /**
     * Locking functionality for the display module.
     * As there are multiple modules that will be competing
     * for the screen, need to control access. Each module
     * can lock/unlock the display using its id assigned by
     * the module base class, and can only draw on the screen
     * if it locked the screen or the screen is nott locked
     */
    void lock(int id);
    void unlock(int id);
    bool isLocked(int id);
    void forceUnlock();

    void setSimon(int lock_id, int state);
    void setTime(int lock_id, int hour, int minute);
    void clearDisplay(int lock_id);
};

const uint8_t* getNumericalBitmap(int bitmap);

#endif