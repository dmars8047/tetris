#ifndef TIMER_H
#define TIMER_H

class Timer
{
private:
    unsigned long long m_PreviousHighPerformace;
    unsigned long long m_CurrentHighPerformace;
    unsigned long long m_PreviousFrameTicks;
    unsigned long long m_CurrentFrameTicks;
    double m_FrameDeltaSeconds;
    int m_DeltaTicks;
    bool m_Paused;
public:
    Timer();
    void StartNewFrame();
    double GetDeltaSeconds() const;
    int GetDeltaMilliSeconds() const;
    void Pause();
    void Unpause();
    bool IsPaused() const;
};

#endif