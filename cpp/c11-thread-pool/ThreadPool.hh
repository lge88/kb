#ifndef THREADPOOL_HH
#define THREADPOOL_HH

#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "Queue.hh"

template<typename Task>
class ThreadPool {
 public:
  ThreadPool(int numThreads, int maxQueueSize);
  ~ThreadPool();

  // Return false if queue is full
  bool schedule(Task t);

  void stop();

 private:
  std::mutex queueMutex_;
  Queue<Task> queue_;
  int maxQueueSize_;

  bool stopRequested_;
  void perThreadFunc(int id);
  std::vector<std::thread> threads_;

  std::mutex ioMutex_;

}; // class ThreadPool

template<typename Task>
ThreadPool<Task>::ThreadPool(int numThreads, int maxQueueSize)
    : maxQueueSize_(maxQueueSize),
      stopRequested_(false)
{
  for (int i = 0; i < numThreads; ++i) {
    threads_.emplace_back(&ThreadPool::perThreadFunc, this, i);
  }
}

template<typename Task>
ThreadPool<Task>::~ThreadPool() {
  stopRequested_ = true;
  for (std::thread& t : threads_) {
    if (t.joinable()) {
      t.join();
    }
  }
}

template<typename Task>
void ThreadPool<Task>::perThreadFunc(int id) {
  {
    std::lock_guard<std::mutex> lock(ioMutex_);
    std::cerr << "thread (" << id << ") started.\n";
  }

  while (!stopRequested_) {
    // - pull a task from task queue if it is not empty
    // - run the task
    Task task;
    bool shouldRun = false;
    {
      std::lock_guard<std::mutex> lock(queueMutex_);
      if (queue_.size() > 0) {
        task = queue_.dequeue();
        shouldRun = true;
      }
    }
    if (shouldRun) task();
    std::this_thread::sleep_for(std::chrono::nanoseconds(100));
  }

  {
    std::lock_guard<std::mutex> lock(ioMutex_);
    std::cerr << "thread (" << id << ") stoped.\n";
  }
}

template<typename Task>
bool ThreadPool<Task>::schedule(Task t) {
  {
    std::lock_guard<std::mutex> lock(queueMutex_);
    if (queue_.size() >= maxQueueSize_) return false;
    queue_.enqueue(t);
  }
  return true;
}

template<typename Task>
void ThreadPool<Task>::stop() {
  stopRequested_ = true;
  for (std::thread& t : threads_) {
    t.join();
  }
}

#endif // THREADPOOL_HH
