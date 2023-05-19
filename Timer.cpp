#include "Timer.h"

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;

    Started = false;
    Paused = false;
}

Timer::~Timer()
{

}

void Timer::start()
{
    Started = true;
    Paused = false;

    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    Paused = false;
    Started = false;
}

void Timer::pause()
{
    if(Started == true && Paused == false)
    {
        Paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    if(Paused == true)
    {
        Paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

int Timer::getTicks()
{
    if(Started == true)
    {
        if(Paused == true)
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }
    }

    return 0;
}

bool Timer::isStarted()
{
    return Started;
}

bool Timer::isPaused()
{
    return Paused;
}
