#ifndef THREAD_POOL_BENCHMARK_STATE_HH
#define THREAD_POOL_BENCHMARK_STATE_HH

#include <iostream>
#include <chrono>
#include <cstdint>

struct ThreadPoolBenchmarkState {
  typedef std::chrono::time_point<std::chrono::system_clock> Timestamp;
  typedef std::chrono::duration<double, std::milli> Duration;

  static inline Timestamp getTimestamp() {
    return std::chrono::system_clock::now();
  }

  Timestamp startedTime_;
  uint64_t totalRequestCompleted_;

  Timestamp lastRecordedTime_;
  uint64_t requestCompletedSinceLast_;
  uint64_t requestDroppedSinceLast_;
  Duration totalLatencySinceLast_;

  int dummy_;

  ThreadPoolBenchmarkState() {
    reset();
  }

  void clearLast() {
    requestCompletedSinceLast_ = 0;
    requestDroppedSinceLast_ = 0;
    totalLatencySinceLast_ = Duration(0.0);
  }

  void reset() {
    totalRequestCompleted_ = 0;
    clearLast();
  }

  double getCurrentThroughput() const {
    return static_cast<double>(requestCompletedSinceLast_) /
        std::chrono::duration<double>(getTimestamp() - lastRecordedTime_).count();
  }

  double getDropRate() const {
    return static_cast<double>(requestDroppedSinceLast_) /
        static_cast<double>(requestDroppedSinceLast_ + requestCompletedSinceLast_);
  }

  double getCurrentAverageLatency() const {
    return totalLatencySinceLast_.count() / static_cast<double>(requestCompletedSinceLast_);
  }

  void writeFormatString(std::ostream& to, bool withHeader = false) const {
    if (withHeader) {
      to << "\n"
         << std::left << std::setw(25) << "Throughput"
         << std::left << std::setw(25) << "Drop Rate"
         << std::left << std::setw(25) << "Avg Latency"
         << std::left << std::setw(25) << "Requests Completed"
         << "\n";
    }

    to << std::left << std::setw(25) << getCurrentThroughput()
       << std::left << std::setw(25) << getDropRate()
       << std::left << std::setw(25) << getCurrentAverageLatency()
       << std::left << std::setw(25) << totalRequestCompleted_
       << "\n";
  }
};


#endif // THREAD_POOL_BENCHMARK_STATE_HH
