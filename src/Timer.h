#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
public:
    Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 getTicks();

    bool isStarted();
    bool isPaused();

private:
    Uint32 mStartTick;

    Uint32 mPausedTick;

    bool mPaused;
    bool mStarted;
};
#endif