#ifndef THREADPOOL_HH
#define THREADPOOL_HH

#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <condition_variable>

#include "RingBuffer.hh"

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
  std::mutex mtx_;
  std::condition_variable cv_;

  RingBuffer<Task> queue_;

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

// Consumer
template<typename Task>
void ThreadPool<Task>::perThreadFunc(int id) {
  std::unique_lock<std::mutex> lock(mtx_);
  Task task;
  while (!stopRequested_) {
    // wait for condition: queue is not empty
    while (queue_.empty()) {
      cv_.wait(lock);
    }
    queue_.dequeue(task);

    task();
  }
}

// Producer
template<typename Task>
bool ThreadPool<Task>::schedule(Task task) {
  std::unique_lock<std::mutex> lock(mtx_);

  bool ok = queue_.enqueue(task);

  lock.unlock();
  cv_.notify_all();
  return ok;
}

#endif // THREADPOOL_HH
