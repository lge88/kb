#ifndef THREAD_POOL_BENCHMARK_STATE_HH
#define THREAD_POOL_BENCHMARK_STATE_HH

#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>

struct ThreadPoolBenchmarkState {
  typedef std::chrono::time_point<std::chrono::system_clock> Timestamp;
  typedef std::chrono::duration<double, std::milli> Duration;

  static inline Timestamp getTimestamp() {
    return std::chrono::system_clock::now();
  }

  Timestamp startedTime_;
  std::atomic<uint64_t> totalRequestCompleted_;

  Timestamp lastRecordedTime_;
  std::atomic<uint64_t> requestSentSinceLast_;
  std::atomic<uint64_t> requestCompletedSinceLast_;
  std::atomic<uint64_t> requestDroppedSinceLast_;
  std::atomic<double> totalLatencySinceLast_;

  uint64_t queueSize_;

  uint64_t dummy_;

  ThreadPoolBenchmarkState() {
    reset();
  }

  void clearLast() {
    requestSentSinceLast_ = 0;
    queueSize_ = 0;
    requestCompletedSinceLast_ = 0;
    requestDroppedSinceLast_ = 0;
    totalLatencySinceLast_ = 0.0;
  }

  void reset() {
    throughput_ = 0.0;
    dropRate_ = 0.0;
    averageLatency_ = 0.0;

    totalRequestCompleted_ = 0;
    clearLast();
    startedTime_ = getTimestamp();
    lastRecordedTime_ = startedTime_;
  }

  void update() {
    throughput_ = static_cast<double>(requestCompletedSinceLast_) /
        std::chrono::duration<double>(getTimestamp() - lastRecordedTime_).count();
    dropRate_ = static_cast<double>(requestDroppedSinceLast_) / static_cast<double>(requestSentSinceLast_);
    averageLatency_ = totalLatencySinceLast_ / static_cast<double>(requestCompletedSinceLast_);

    clearLast();
    lastRecordedTime_ = getTimestamp();
  }

  double getCurrentThroughput() const { return throughput_; }

  double getDropRate() const { return dropRate_; }

  double getCurrentAverageLatency() const { return averageLatency_; }

  void writeFormatString(std::ostream& to, bool withHeader = false) const {
    static const int w = 20;
    if (withHeader) {
      to << "\n"
         << std::left << std::setw(w) << "Throughput"
         << std::left << std::setw(w) << "Queue Size"
         << std::left << std::setw(w) << "Drop Rate"
         << std::left << std::setw(w) << "Avg Latency"
         << std::left << std::setw(w) << "Total Completed"
         << "\n";
    }

    to << std::left << std::setw(w) << getCurrentThroughput()
       << std::left << std::setw(w) << queueSize_
       << std::left << std::setw(w) << getDropRate()
       << std::left << std::setw(w) << getCurrentAverageLatency()
       << std::left << std::setw(w) << totalRequestCompleted_
       << "\n";
  }

 private:
  double throughput_, dropRate_, averageLatency_;
};


#endif // THREAD_POOL_BENCHMARK_STATE_HH
