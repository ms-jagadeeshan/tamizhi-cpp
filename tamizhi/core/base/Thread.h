#pragma once

#include "tamizhi/core/base/Macros.h"
#include "tamizhi/core/base/Memory.h"
#include <functional>
#include <mutex>
#include <thread>

class crThread
{
    using crThreadCallback = std::function<void()>;

public:
    // Constructors.
    crThread(const std::string& name = "");
    virtual ~crThread() = default;

    int exec(const bool& threaded = false);
    int execOnce();
    virtual void close();

    // Setters.
    void setFrequency(const double& freq);
    // Set the callback.
    void setCallback(const crThreadCallback& callback);

    // Is the thread running.
    bool isRunning() const;
    // Pause the exection.
    void pause();
    // Resume the execution.
    void resume();
    // Kill the thread.
    void kill();

protected:
    // Start the thread.
    void startThread();
    // Execute the callback.
    void execInternal();

protected:
    // Is Process closed.
    bool mIsClosed;
    // Is Process killed.
    bool mProcessKilled = false;
    // Is the thread running.
    bool mIsRunning = false;
    // Delay time in milliseconds.
    double mDelayTime = 1000;
    // Mutex for threaded execution.
    std::mutex mLifeMtx;
    // Store the callback.
    crThreadCallback mFunctionToExecute = nullptr;
    // Thread.
    tmzSP<std::thread> mThread;
    // Store the name.
    std::string mName = "";
};
