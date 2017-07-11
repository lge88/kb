#ifndef THREAD_POOL_BENCHMARK_HH
#define THREAD_POOL_BENCHMARK_HH

#include <atomic>

class ThreadPoolBenchmark {
 public:
  struct Options {
    // pool options
    int numThreads_ = 4;
    int maxQueueSize_ = 100;

    // load options
    int singleExecutionLatency_ = 20;
    int qps_ = 250;
    int goal_ = qps_ * 10;
  };

  ThreadPoolBenchmark(const Options& options);

  void start();
  void stop();

  double getCurrentThroughput() const;
  double getOverallThroughput() const;
  double getScheduleFailedRate() const ;

 private:
  Options options_;

  struct State {
    std::atomic<int> requestCompleted_(0);
    double startTime_ = -1.0;
    double lastRecordedTime_ = -1.0;
    int scheduleFailed_ = 0;
    std::mutex ioMutex_;
  };
  State state_;

  struct Task {
    Task(int checkInterval, int latencyMilliseconds, State& sharedState);
    void operator() ();
   private:
    int interval_, latency_;
    State& state_;
  };

}; // class ThreadPoolBenchmark

namespace {

inline double getCurrentMilliseconds() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()).count();
}

} // namespace

ThreadPoolBenchmark::ThreadPoolBenchmark(const Options& options)
    : options_(options)
{}

void ThreadPoolBenchmark::start() {
  ThreadPool<Task> pool(options_.numThreads, options_.maxQueueSize);

  state_.startTime_ = getCurrentMilliseconds();
  state_.lastRecordedTime_ = state_.startTime_;
  while (state_.requestCompleted < options.goal_) {
    Task task(options.qps_, options.singleExecutionLatency_, state_);
    bool scheduled = pool.schedule(task);
    state_.scheduleFailed_ += scheduled ? 0 : 1;
    int thinkTime = 1000000 / qps;
    std::this_thread::sleep_for(std::chrono::microseconds(thinkTime));
  }

  pool.stop();
}

ThreadPoolBenchmark::Task::Task(int checkInterval, int latencyMilliseconds, State& sharedState)
    : interval_(checkInterval),
      latency_(latencyMilliseconds),
      state_(sharedState) {}

void ThreadPoolBenchmark::Task::operator() () {
  // TODO: simulate busy work for given latencyMilliseconds.
  // sleep_for won't cause CPU?
  std::this_thread::sleep_for(std::chrono::milliseconds(latency_));
  int count = state_.requestCompleted++;
  if (count % interval_ == 0) {
    double now = getCurrentMilliseconds();
    double totalElapsed = now - state_.startTime_;
    double elapsedSinceLast = now - state_.lastRecordedTime_;
    // double overallThroughput = static_cast<double>(count) / totalElapsed * 1000;
    double currentThroughput = static_cast<double>(interval_) / elapsedSinceLast * 1000;
    bool printHeader = count % (5 * interval_) == 0;
    {
      std::lock_guard<std::mutex> lock(state_.ioMutex_);

      if (printHeader) {
        std::cerr << "\n"
                  << std::left << std::setw(25) << "current throughput"
            // << std::left << std::setw(25) << "overall throughput"
                  << std::left << std::setw(25) << "requests completed"
                  << std::left << std::setw(25) << "schedule failed since last"
                  << "\n";
      }
      std::cerr << std::left << std::setw(25) << currentThroughput
          // << std::left << std::setw(25) << overallThroughput
                << std::left << std::setw(25) << count
                << std::left << std::setw(25) << notScheduled
                << "\n";
    }
    state_.lastRecordedTime = now;
    state_.scheduleFailed_ = 0;
  }
}

#endif // THREAD_POOL_BENCHMARK_HH
