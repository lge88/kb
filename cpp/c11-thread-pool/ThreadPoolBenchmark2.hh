#ifndef THREAD_POOL_BENCHMARK_HH
#define THREAD_POOL_BENCHMARK_HH

#include <atomic>
#include "ThreadPoolBenchmarkState.hh"

struct ThreadPoolBenchmarkOptions {
  // pool options (consumer)
  uint32_t numPoolThreads_ = 4;
  uint32_t queueCapacity_ = 100;

  // client options (producer)
  // How many threads to use to generate requests
  uint32_t numClientThreads_ = 1;

  // How often should background thread to check the benchmark state?
  uint64_t refreshIntervalMilliseconds_ = 100;
};

// template<typename Task>
class ThreadPoolBenchmark {
 public:
  ThreadPoolBenchmark();
  ThreadPoolBenchmark(const ThreadPoolBenchmarkOptions& options);
  ~ThreadPoolBenchmark();
  ThreadPoolBenchmarkOptions options_;

  void start();
  void stop();

  ThreadPoolBenchmarkState getState() const { return state_; }

  static inline double getCurrentMilliseconds() {
    return std::chrono::duration<double, std::milli>(
        std::chrono::system_clock::now().time_since_epoch()).count();
  }

 private:
  ThreadPoolBenchmarkState state_;

  struct Task {
    Task();
    Task(ThreadPoolBenchmarkState::Timestamp started, ThreadPoolBenchmarkState* sharedState = nullptr);
    void operator() ();

   private:
    ThreadPoolBenchmarkState::Timestamp started_;
    ThreadPoolBenchmarkState* state_;
  };

  bool stopRequested_ = false;
  void benchmarkThreadFunc();
  void stateUpdateThreadFunc();
  std::vector<std::thread> threads_;

  std::unique_ptr<ThreadPool<Task> > pool_;

}; // class ThreadPoolBenchmark

ThreadPoolBenchmark::ThreadPoolBenchmark(const ThreadPoolBenchmarkOptions& options)
    : options_(options) {}

ThreadPoolBenchmark::ThreadPoolBenchmark() {}

ThreadPoolBenchmark::~ThreadPoolBenchmark() {
  stop();
}

void ThreadPoolBenchmark::start() {
  stop();

  stopRequested_ = false;
  pool_.reset(new ThreadPool<Task>(options_.numPoolThreads_, options_.queueCapacity_));
  state_.reset();
  state_.startedTime_ = ThreadPoolBenchmarkState::getTimestamp();
  state_.lastRecordedTime_ = state_.startedTime_;
  for (int i = 0; i < options_.numClientThreads_; ++i) {
    threads_.emplace_back(&ThreadPoolBenchmark::benchmarkThreadFunc, this);
  }
  threads_.emplace_back(&ThreadPoolBenchmark::stateUpdateThreadFunc, this);
}

void ThreadPoolBenchmark::stop() {
  stopRequested_ = true;
  for (std::thread& t : threads_) {
    if (t.joinable()) {
      t.join();
    }
  }
}

void ThreadPoolBenchmark::benchmarkThreadFunc() {
  // const uint64_t interval = options_.qps_ == 0 ? 1000000 : options_.qps_;
  // const uint64_t latency = options_.singleExecutionLatency_;
  while (!stopRequested_) {
    Task task(ThreadPoolBenchmarkState::getTimestamp(), &state_);
    bool scheduled = pool_->schedule(task);
    state_.requestDroppedSinceLast_ += scheduled ? 0 : 1;
    // if (options_.qps_ > 0) {
    //   uint64_t thinkTime = 1000000 / options_.qps_;
    // std::this_thread::sleep_for(std::chrono::microseconds(1000));
    // }
  }
}

void ThreadPoolBenchmark::stateUpdateThreadFunc() {
  while (!stopRequested_) {
    std::this_thread::sleep_for(std::chrono::milliseconds(options_.refreshIntervalMilliseconds_));
    state_.clearLast();
    state_.lastRecordedTime_ = ThreadPoolBenchmarkState::getTimestamp();
  }
}

ThreadPoolBenchmark::Task::Task() {}

ThreadPoolBenchmark::Task::Task(
    ThreadPoolBenchmarkState::Timestamp started,
    ThreadPoolBenchmarkState* sharedState)
    : started_(started),
      state_(sharedState) {}

void ThreadPoolBenchmark::Task::operator() () {
  // TODO: simulate busy work for given latencyMilliseconds.
  // sleep_for won't cause user CPU...
  // std::this_thread::sleep_for(std::chrono::milliseconds(latency_));

  // Do some work...

  state_->requestCompletedSinceLast_++;
  state_->totalRequestCompleted_++;
  state_->totalLatencySinceLast_ += ThreadPoolBenchmarkState::getTimestamp() - started_;
}

#endif // THREAD_POOL_BENCHMARK_HH
