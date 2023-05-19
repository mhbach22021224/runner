#ifndef Timer_h
#define Timer_h

#include "CommonFunction.h"

class Timer{
public:
    Timer();
    ~Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    int getTicks();

    bool isPaused();
    bool isStarted();
private:
    int startTicks;
    int pausedTicks;

    bool Paused;
    bool Started;
};
#endif // Timer_h
