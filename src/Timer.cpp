#include "Timer.h"

Timer::Timer()
{
    mStartTick = 0;
    mPausedTick = 0;

    mPaused = false;
    mStarted = false;
}

void Timer::start()
{
    mStarted = true;
    mPaused = false;
    mStartTick = SDL_GetTicks();
    mPausedTick = 0;
}

void Timer::stop()
{
    mStarted = false;
    mPaused = false;

    mStartTick = 0;
    mPausedTick = 0;
}

void Timer::pause()
{
    if(mStarted && !mPaused)
    {
        mPaused = true;
        mPausedTick = SDL_GetTicks() - mStartTick;
        mStartTick = 0;
    }
}

void Timer::unpause()
{
    if (mStarted && mPaused)
    {
        mPaused = false;
        mStartTick = SDL_GetTicks() - mPausedTick;
        mPausedTick = 0;
    }
}

Uint32 Timer::getTicks()
{
    Uint32 time = 0;

    if (mStarted)
    {
        if (mPaused)
        {
            time = mPausedTick;
        }
        else
        {
            time = SDL_GetTicks() - mStartTick;
        }
    }

    return time;
}

bool Timer::isStarted()
{
    return mStarted;
}

bool Timer::isPaused()
{
    return mPaused && mStarted;
}

