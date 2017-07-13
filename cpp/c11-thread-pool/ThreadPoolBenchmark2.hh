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

  // How many nanoseconds should client wait before firing next request.
  // 0 means no wait
  uint64_t thinkTimeNanoseconds_ = 0;

  // How often should background thread to check the benchmark state?
  uint64_t refreshIntervalMilliseconds_ = 100;

  // Number of repetations the cpu insive code runs
  uint64_t loadRepeat_ = 1000000;
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

  const ThreadPoolBenchmarkState& getState() const { return state_; }

  static inline double getCurrentMilliseconds() {
    return std::chrono::duration<double, std::milli>(
        std::chrono::system_clock::now().time_since_epoch()).count();
  }

 private:
  ThreadPoolBenchmarkState state_;

  struct Task {
    Task();
    Task(ThreadPoolBenchmarkState::Timestamp started,
         uint64_t repeat_ = 1000000,
         ThreadPoolBenchmarkState* sharedState = nullptr);
    void operator() ();

   private:
    uint64_t repeat_;
    ThreadPoolBenchmarkState::Timestamp started_;
    ThreadPoolBenchmarkState* state_;

    inline uint64_t h(uint64_t x) {
      x = ((x >> 16) ^ x) * 0x45d9f3b;
      x = ((x >> 16) ^ x) * 0x45d9f3b;
      x = (x >> 16) ^ x;
      return x;
    }

    inline uint64_t work(uint64_t x) {
      for (uint64_t i = 0; i < repeat_; ++i) x = h(x);
      return x;
    }
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
    Task task(ThreadPoolBenchmarkState::getTimestamp(), options_.loadRepeat_, &state_);
    bool scheduled = pool_->schedule(task);
    state_.requestSentSinceLast_++;
    state_.requestDroppedSinceLast_ += scheduled ? 0 : 1;
    if (options_.thinkTimeNanoseconds_ > 0) {
      std::this_thread::sleep_for(std::chrono::nanoseconds(options_.thinkTimeNanoseconds_));
    }
  }
}

void ThreadPoolBenchmark::stateUpdateThreadFunc() {
  while (!stopRequested_) {
    std::this_thread::sleep_for(std::chrono::milliseconds(options_.refreshIntervalMilliseconds_));
    state_.update();
    state_.queueSize_ = pool_->queueSize();
  }
}

ThreadPoolBenchmark::Task::Task() {}

ThreadPoolBenchmark::Task::Task(
    ThreadPoolBenchmarkState::Timestamp started,
    uint64_t repeat,
    ThreadPoolBenchmarkState* sharedState)
    : started_(started),
      repeat_(repeat),
      state_(sharedState) {}

void ThreadPoolBenchmark::Task::operator() () {
  // TODO: simulate busy work for given latencyMilliseconds.
  // sleep_for won't cause user CPU...
  // std::this_thread::sleep_for(std::chrono::milliseconds(latency_));

  // Do some work...
  // Needs to write to dummy_ in order for compiler to optimize the value out.
  state_->dummy_ = work(state_->totalRequestCompleted_);

  state_->requestCompletedSinceLast_++;
  state_->totalRequestCompleted_++;

  double elapsed = ThreadPoolBenchmarkState::Duration(ThreadPoolBenchmarkState::getTimestamp() - started_).count();
  auto current = state_->totalLatencySinceLast_.load();
  while (!state_->totalLatencySinceLast_.compare_exchange_weak(current, current + elapsed));
}

#endif // THREAD_POOL_BENCHMARK_HH
