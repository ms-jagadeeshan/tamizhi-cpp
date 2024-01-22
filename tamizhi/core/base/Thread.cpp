#include "tamizhi/core/base/Thread.h"
#include "tamizhi/core/base/Time.h"

/********************************************************************/

crThread::crThread(const std::string& name)
    : mName(name)
{
}

/********************************************************************/

int crThread::exec(const bool& threaded)
{
    if (threaded)
        startThread();
    else
        execInternal();
    return EXIT_SUCCESS;
}

/********************************************************************/

int crThread::execOnce()
{
    checkAndReturnValue(mFunctionToExecute != nullptr, "[Thread] Empty callback", EXIT_FAILURE);
    checkAndReturnValue(!mIsRunning, "[Thread] Thread is already running", EXIT_FAILURE);

    mThread = std::make_shared<std::thread>(mFunctionToExecute);
    mIsClosed = false;
    mIsRunning = true;
    mProcessKilled = false;
    return EXIT_SUCCESS;
}

/********************************************************************/

void crThread::close()
{
    checkAndReturn(!mIsClosed, "[Thread] Thread is already closed");

    if (mThread)
        mThread->detach();
    kill();
    mIsClosed = true;
    mIsRunning = false;
}

/********************************************************************/

void crThread::setFrequency(const double& freq)
{
    checkAndReturn(freq != 0, "[Thread] Frequency cannot be zero");
    mDelayTime = 1000.0 / freq;
}

/********************************************************************/

void crThread::setCallback(const crThreadCallback& callback)
{
    std::lock_guard<std::mutex> lock(mLifeMtx);
    mFunctionToExecute = callback;
}

/********************************************************************/

bool crThread::isRunning() const
{
    return mIsRunning;
}

/********************************************************************/

void crThread::pause()
{
    std::lock_guard<std::mutex> lock(mLifeMtx);
    mIsRunning = false;
}

/********************************************************************/

void crThread::resume()
{
    std::lock_guard<std::mutex> lock(mLifeMtx);
    mIsRunning = true;
}

/********************************************************************/

void crThread::kill()
{
    std::scoped_lock lock(mLifeMtx);
    mProcessKilled = true;
}

/********************************************************************/

void crThread::startThread()
{
    if (!mIsRunning)
    {
        mThread = std::make_shared<std::thread>(&crThread::execInternal, this);
        mIsClosed = false;
        mIsRunning = true;
        mProcessKilled = false;
    }
}

/********************************************************************/

void crThread::execInternal()
{
    checkAndReturn(mFunctionToExecute != nullptr, "[Thread] Empty callback");
    while (true)
    {
        tmzTimePointSC startTime = getCurrentTimeSC();
        {
            std::lock_guard<std::mutex> lock(mLifeMtx);
            if (mProcessKilled)
            {
                break;
            }

            if (mFunctionToExecute && mIsRunning)
            {
                try
                {
                    mFunctionToExecute();
                }
                catch (const std::bad_function_call& e)
                {
                }
            }
        }

        tmzDurationMS elapsedTime = getCurrentTimeSC() - startTime;
        double diff = mDelayTime - elapsedTime.count();
        diff = diff < 0 ? 0 : diff;
        tmzSleep(diff);
    }

    {
        std::lock_guard<std::mutex> lock(mLifeMtx);
        mIsRunning = false;
    }
}

/********************************************************************/
