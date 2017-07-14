#ifndef THREADPOOL_HH
#define THREADPOOL_HH

#include <atomic>
#include <iostream>
#include <mutex>
#include <memory>
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

  inline size_t queueSize() const {
    size_t count = 0;
    for (size_t i = 0; i < workers_.size(); ++i) {
      const Worker& worker = *workers_[i];
      std::lock_guard<std::mutex> l(worker.mtx_);
      count += worker.queue_.size();
    }
    return count;
  }

 private:
  std::mutex mtx_;

  struct Worker {
    int id_;
    mutable std::mutex mtx_;
    mutable std::condition_variable cv_;
    RingBuffer<Task> queue_;
    Worker(int id, size_t queueSize): id_(id), queue_(queueSize) {}
  };
  std::vector<std::unique_ptr<Worker> > workers_;
  size_t nextThreadId_;

  bool stopRequested_;
  void perThreadFunc(int id);
  std::vector<std::thread> threads_;
}; // class ThreadPool

template<typename Task>
ThreadPool<Task>::ThreadPool(int numThreads, int queueCapacity)
    : nextThreadId_(0),
      stopRequested_(false)
{
  int baseQueueSize = queueCapacity / numThreads;
  int remained = queueCapacity % numThreads;
  for (int i = 0; i < numThreads; ++i) {
    int singleQueueSize = baseQueueSize;
    if (remained > 0) {
      singleQueueSize += 1;
      remained -= 1;
    }
    workers_.emplace_back(new Worker(i, singleQueueSize));
  }

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
  Worker& worker = *workers_[id];
  std::unique_lock<std::mutex> lock(worker.mtx_, std::defer_lock);
  Task task;
  while (!stopRequested_) {
    // wait for condition: queue is not empty
    lock.lock();
    while (worker.queue_.empty()) {
      worker.cv_.wait(lock);
    }
    worker.queue_.dequeue(task);
    lock.unlock();

    task();
  }
}

// Producer
template<typename Task>
bool ThreadPool<Task>::schedule(Task task) {
  // Pick a worker use round-robin
  // Just keep trying for one pass of all the thread.
  std::lock_guard<std::mutex> l(mtx_);
  const size_t numWorkers = workers_.size(), retries = numWorkers;
  for (size_t i = 0; i < retries; ++i) {
    Worker& worker = *workers_[nextThreadId_];
    nextThreadId_ = (nextThreadId_ + 1) % numWorkers;

    {
      std::unique_lock<std::mutex> lock(worker.mtx_);
      if (worker.queue_.enqueue(task)) {
        lock.unlock();
        worker.cv_.notify_all();
        return true;
      }
    }
  }
  return false;
}

#endif // THREADPOOL_HH
