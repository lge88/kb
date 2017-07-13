#ifndef THREADPOOL_HH
#define THREADPOOL_HH

#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "Queue.hh"

// Task is a:
// - DefaultConstructible
// - CopyAssignable
// - Defined void operator() (void)
template<typename Task>
class ThreadPool {
 public:
  ThreadPool(int numThreads, int queueCapacity);
  ~ThreadPool();

  // Return false if queue is full
  bool schedule(Task task);

  inline size_t queueSize() const { return queue_.size(); }

 private:
  Queue<Task> queue_;

  bool stopRequested_;
  void perThreadFunc(int id);
  std::vector<std::thread> threads_;
}; // class ThreadPool

template<typename Task>
ThreadPool<Task>::ThreadPool(int numThreads, int queueCapacity)
    : queue_(queueCapacity),
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
    if (t.joinable()) t.join();
  }
}

template<typename Task>
void ThreadPool<Task>::perThreadFunc(int id) {
  // Busy wait:
  // - pull a task from task queue if it is not empty
  // - run the task
  Task task;
  while (!stopRequested_) {
    if (queue_.dequeue(task)) task();
    // Busy waiting cost high cpu but improve latency.
    // std::this_thread::sleep_for(std::chrono::nanoseconds(100000));
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
    // std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    // std::this_thread::sleep_for(std::chrono::nanoseconds(0));
  }
}

template<typename Task>
bool ThreadPool<Task>::schedule(Task task) {
  return queue_.enqueue(task);
}

#endif // THREADPOOL_HH
