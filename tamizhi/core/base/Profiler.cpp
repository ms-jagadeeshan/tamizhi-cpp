#include "tamizhi/core/base/Profiler.h"
#include "tamizhi/core/base/Macros.h"

/********************************************************************/

crTimeProfiler::crTimeProfiler(const std::string& name, bool useHighResolutionClock)
    : mUseHighResolutionClock(useHighResolutionClock), mName(name)
{
    start();
}

/********************************************************************/

void crTimeProfiler::start()
{
    if (mUseHighResolutionClock)
        mStartHRC = getCurrentTimeHRC();
    else
        mStartSC = getCurrentTimeSC();
}

/********************************************************************/

void crTimeProfiler::stop()
{
    if (mUseHighResolutionClock)
        mEndHRC = getCurrentTimeHRC();
    else
        mEndSC = getCurrentTimeSC();
}

/********************************************************************/

void crTimeProfiler::reset()
{
}

/********************************************************************/

double crTimeProfiler::getTimeElapsed()
{
    std::chrono::duration<double> elapsedDuration;
    if (mUseHighResolutionClock)
    {
        mEndHRC = getCurrentTimeHRC();
        elapsedDuration = mEndHRC - mStartHRC;
    }
    else
    {
        mEndSC = getCurrentTimeSC();
        elapsedDuration = mEndSC - mStartSC;
    }

    return elapsedDuration.count();
}

/********************************************************************/

void crTimeProfiler::printTimeElapsed()
{
    if (mUseHighResolutionClock)
    {
        auto currentHRC = getCurrentTimeHRC();
        std::chrono::duration<double> elapsedDuration = currentHRC - mStartHRC;
        tmzPrint("[%s] Time elapsed since start is : %f sec\n", mName.c_str(), elapsedDuration.count());
    }
    else
    {
        auto currentSC = getCurrentTimeSC();
        std::chrono::duration<double> elapsedDuration = currentSC - mStartSC;
        tmzPrint("[%s] Time elapsed since start is : %f sec\n", mName.c_str(), elapsedDuration.count());
    }
}

/********************************************************************/
