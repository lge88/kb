#ifndef THREAD_POOL_BENCHMARK_HH
#define THREAD_POOL_BENCHMARK_HH

#include <atomic>

namespace {


} // namespace

struct ThreadPoolBenchmarkOptions {
  // pool options
  int numThreads_ = 4;
  int queueCapacity_ = 100;

  // load options
  // How many threads to use to generate requests
  int numClientThreads_ = 2;

  // latency for single task execution.
  int singleExecutionLatency_ = 20;

  // qps <=0 means do not break on consecutive requests, request as fast as possible.
  int qps_ = 250;
};

struct ThreadPoolBenchmarkState {
  std::atomic<uint64_t> requestCompleted_;
  double startTime_;
  double lastRecordedTime_;
  std::atomic<uint64_t> scheduleFailed_;
  double overallThroughput_;
  double currentThroughput_;
  double scheduleFailRate_;
  ThreadPoolBenchmarkState() { reset(); }
  void reset() {
    requestCompleted_ = 0;
    startTime_ = -1.0;
    lastRecordedTime_ = -1.0;
    scheduleFailed_ = 0;
    overallThroughput_ = 0.0;
    currentThroughput_ = 0.0;
    scheduleFailRate_ = 0.0;
  }

  ThreadPoolBenchmarkState(const ThreadPoolBenchmarkState& other) {
    requestCompleted_ = other.requestCompleted_.load();
    startTime_ = other.startTime_;
    lastRecordedTime_ = other.lastRecordedTime_;
    scheduleFailed_ = other.scheduleFailed_.load();
    overallThroughput_ = other.overallThroughput_;
    currentThroughput_ = other.currentThroughput_;
    scheduleFailRate_ = other.scheduleFailRate_;
  }
};

class ThreadPoolBenchmark {
 public:

  ThreadPoolBenchmark();
  ThreadPoolBenchmark(const ThreadPoolBenchmarkOptions& options);
  ~ThreadPoolBenchmark();
  ThreadPoolBenchmarkOptions options_;

  void start();
  void stop();

  inline ThreadPoolBenchmarkState getState() const {
    return state_;
  }

  static inline double getCurrentMilliseconds() {
    return std::chrono::duration<double, std::milli>(
        std::chrono::system_clock::now().time_since_epoch()).count();
  }

 private:
  ThreadPoolBenchmarkState state_;

  struct Task {
    Task(uint64_t checkInterval = 0, uint64_t latencyMilliseconds = 0, ThreadPoolBenchmarkState* sharedState = nullptr);
    void operator() ();
   private:
    int interval_, latency_;
    ThreadPoolBenchmarkState* state_;
  };

  bool stopRequested_ = false;
  void benchmarkThreadFunc();
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
  pool_.reset(new ThreadPool<Task>(options_.numThreads_, options_.queueCapacity_));
  state_.reset();
  state_.startTime_ = getCurrentMilliseconds();
  state_.lastRecordedTime_ = state_.startTime_;
  for (int i = 0; i < options_.numClientThreads_; ++i) {
    threads_.emplace_back(&ThreadPoolBenchmark::benchmarkThreadFunc, this);
  }
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
  const uint64_t interval = options_.qps_ == 0 ? 1000000 : options_.qps_;
  const uint64_t latency = options_.singleExecutionLatency_;
  while (!stopRequested_) {
    Task task(interval, latency, &state_);
    bool scheduled = pool_->schedule(task);
    state_.scheduleFailed_ += scheduled ? 0 : 1;
    if (options_.qps_ > 0) {
      uint64_t thinkTime = 1000000 / options_.qps_;
      std::this_thread::sleep_for(std::chrono::microseconds(thinkTime));
    }
  }
}

ThreadPoolBenchmark::Task::Task(uint64_t checkInterval, uint64_t latencyMilliseconds, ThreadPoolBenchmarkState* sharedState)
    : interval_(checkInterval),
      latency_(latencyMilliseconds),
      state_(sharedState) {}

void ThreadPoolBenchmark::Task::operator() () {
  // TODO: simulate busy work for given latencyMilliseconds.
  // sleep_for won't cause user CPU...
  // std::this_thread::sleep_for(std::chrono::milliseconds(latency_));

  uint64_t count = ++state_->requestCompleted_;
  if (count % interval_ == 0) {
    double now = getCurrentMilliseconds();
    double totalElapsed = now - state_->startTime_;
    double elapsedSinceLast = now - state_->lastRecordedTime_;
    state_->overallThroughput_ = static_cast<double>(count) / totalElapsed * 1000;
    state_->currentThroughput_ = static_cast<double>(interval_) / elapsedSinceLast * 1000;
    state_->scheduleFailRate_ = static_cast<double>(state_->scheduleFailed_) / static_cast<double>(state_->scheduleFailed_ + interval_);
    state_->lastRecordedTime_ = now;
    state_->scheduleFailed_ = 0;
  }
}

#endif // THREAD_POOL_BENCHMARK_HH
