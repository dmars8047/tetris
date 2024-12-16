#if __APPLE__
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <iostream>

#include "timer.hpp"

Timer::Timer()
{
    m_CurrentFrameTicks = 0;
    m_PreviousFrameTicks = 0;
    m_Paused = false;
}

void Timer::StartNewFrame()
{
    m_PreviousHighPerformace = m_CurrentHighPerformace;
    m_CurrentHighPerformace = SDL_GetPerformanceCounter();
    m_PreviousFrameTicks = m_CurrentFrameTicks;
    m_CurrentFrameTicks = SDL_GetTicks64();
    m_DeltaTicks = (m_CurrentFrameTicks - m_PreviousFrameTicks);
    m_FrameDeltaSeconds = (m_CurrentHighPerformace - m_PreviousHighPerformace) / (double)SDL_GetPerformanceFrequency();
}

int Timer::GetDeltaMilliSeconds() const
{
    return m_DeltaTicks;
}

void Timer::Pause()
{
    m_Paused = true;
}

void Timer::Unpause()
{
    m_Paused = false;
}

bool Timer::IsPaused() const
{
    return m_Paused;
}

double Timer::GetDeltaSeconds() const
{
    return m_FrameDeltaSeconds;
}