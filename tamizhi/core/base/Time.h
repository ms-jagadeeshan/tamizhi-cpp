#pragma once

#include <chrono>
#include <thread>

typedef std::chrono::time_point<std::chrono::system_clock> tmzTimePoint;
typedef std::chrono::time_point<std::chrono::steady_clock> tmzTimePointSC;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> tmzTimePointHRC;

typedef std::chrono::duration<double> tmzDuration;
typedef std::chrono::duration<double, std::milli> tmzDurationMS;
typedef std::chrono::duration<double, std::nano> tmzDurationNS;

/********************************************************************/

inline tmzTimePoint getCurrentTime()
{
    return std::chrono::system_clock::now();
}

/********************************************************************/

inline tmzTimePointSC getCurrentTimeSC()
{
    return std::chrono::steady_clock::now();
}

/********************************************************************/

inline tmzTimePointHRC getCurrentTimeHRC()
{
    return std::chrono::high_resolution_clock::now();
}

/********************************************************************/

// Set the ratio to 1000 for milliseconds, 1 for microseconds
inline void tmzSleep(const double& duration, const int& ratio = 1000)
{
    std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(duration * ratio)));
}

/********************************************************************/
