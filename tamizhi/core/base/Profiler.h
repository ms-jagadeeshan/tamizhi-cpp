#pragma once

#include "tamizhi/core/base/Time.h"

#ifdef ENABLE_PROFILER
#include <gperftools/profiler.h>
#else
#define ProfilerStart(...) (void)(0)
#define ProfilerStop() (void)(0)
#endif

class crTimeProfiler
{
public:
    // Constructor.
    explicit crTimeProfiler(const std::string& name = "", bool useHighResolutionClock = false);
    ~crTimeProfiler() = default;

    // Start.
    void start();
    // Stop.
    void stop();
    // Reset timer.
    void reset();
    // Get elapsed time since start.
    double getTimeElapsed();
    // Print time elapsed.
    void printTimeElapsed();

private:
    // Stores the steady clock for start and end.
    tmzTimePointSC mStartSC, mEndSC;
    // Store the high resolution clock for start and end.
    tmzTimePointHRC mStartHRC, mEndHRC;
    // Use high resolution clock.
    bool mUseHighResolutionClock = false;
    // Name.
    std::string mName = "";
};
