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
  ThreadPool(int numThreads, int queueCapacity);
  ~ThreadPool();

  // Return false if queue is full
  bool schedule(Task t);

 private:
  Queue<Task> queue_;

  bool stopRequested_;
  void perThreadFunc(int id);
  std::vector<std::thread> threads_;

  std::mutex ioMutex_;

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
    if (t.joinable()) {
      t.join();
    }
  }
}

template<typename Task>
void ThreadPool<Task>::perThreadFunc(int id) {
  // {
  //   std::lock_guard<std::mutex> lock(ioMutex_);
  //   std::cerr << "thread (" << id << ") started.\n";
  // }

  // Busy wait
  while (!stopRequested_) {
    // - pull a task from task queue if it is not empty
    // - run the task
    Task task;
    if (queue_.dequeue(task)) {
      task();
    }
    // std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));
  }

  // {
  //   std::lock_guard<std::mutex> lock(ioMutex_);
  //   std::cerr << "thread (" << id << ") stoped.\n";
  // }
}

template<typename Task>
bool ThreadPool<Task>::schedule(Task task) {
  return queue_.enqueue(task);
}

#endif // THREADPOOL_HH
