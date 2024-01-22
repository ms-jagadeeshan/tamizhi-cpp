#include "tamizhi/core/base/ThreadPool.h"

/********************************************************************/

crThreadPool::crThreadPool(size_t threadCount)
    : mStop(false)
{
    initializeThreads(threadCount);
}

/********************************************************************/

crThreadPool::~crThreadPool()
{
    shutdown();
}

/********************************************************************/

void crThreadPool::setThreadCount(size_t newThreadCount)
{
    std::unique_lock<std::mutex> lock(mMutex);
    if (newThreadCount != mThreads.size())
    {
        mStop = true;
        mCondition.notify_all();
        for (auto& thread : mThreads)
        {
            thread.join();
        }

        mThreads.clear();
        initializeThreads(newThreadCount);
        mStop = false;
    }
}

/********************************************************************/

void crThreadPool::start()
{
    for (auto& thread : mThreads)
    {
        thread = std::thread([this] {
            while (!mStop)
            {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mMutex);
                    mCondition.wait(lock, [this] { return mStop || !mTasks.empty(); });
                    if (mStop && mTasks.empty())
                    {
                        return;
                    }
                    task = std::move(mTasks.front());
                    mTasks.pop();
                }
                task();
            }
        });
    }
}

/********************************************************************/

bool crThreadPool::isIdle()
{
    std::unique_lock<std::mutex> lock(mMutex);
    return mTasks.empty();
}

/********************************************************************/

void crThreadPool::waitForAllTasks()
{
    std::unique_lock<std::mutex> lock(mMutex);
    mCondition.wait(lock, [this] { return mTasks.empty(); });
}

/********************************************************************/

void crThreadPool::shutdown()
{
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mStop = true;
    }
    mCondition.notify_all();
    for (auto& thread : mThreads)
    {
        thread.join();
    }
}

/********************************************************************/

void crThreadPool::initializeThreads(size_t threadCount)
{
    mThreads.reserve(threadCount);
    for (size_t i = 0; i < threadCount; ++i)
    {
        mThreads.emplace_back();
    }
}

/********************************************************************/
