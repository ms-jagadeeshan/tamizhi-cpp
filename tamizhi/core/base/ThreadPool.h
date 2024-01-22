#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class crThreadPool
{
public:
    // Constructors and destructors.
    explicit crThreadPool(size_t threadCount);
    ~crThreadPool();

    // Set the thread count.
    void setThreadCount(size_t newThreadCount);

    // Start the thread pool to work.
    void start();
    // Enqueue the task.
    template <class F, class... Args>
    void enqueue(F&& task, Args&&... args);
    // Is the thread pool idle.
    bool isIdle();
    // Wait for all tasks to finish.
    void waitForAllTasks();
    // Shutdown the thread pool.
    void shutdown();

private:
    // Initialize the threads.
    void initializeThreads(size_t threadCount);

private:
    std::vector<std::thread> mThreads;
    std::queue<std::function<void()>> mTasks;
    std::mutex mMutex;
    std::condition_variable mCondition;
    std::atomic<bool> mStop;
};

template <class F, class... Args>
void crThreadPool::enqueue(F&& task, Args&&... args)
{
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mTasks.emplace(std::bind(std::forward<F>(task), std::forward<Args>(args)...));
    }
    mCondition.notify_one();
}
