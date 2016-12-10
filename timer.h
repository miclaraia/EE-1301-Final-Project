class MyTimer {
public:
    unsigned int timer;
    int duration;
    bool active;
    void *run();

    bool check();
    void reset();

    MyTimer(unsigned int timer, int duration);
};
