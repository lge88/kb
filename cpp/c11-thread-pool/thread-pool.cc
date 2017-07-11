#include <iostream>
#include <iomanip>

#include "ThreadPool.hh"
#include "ThreadPoolBenchmark.hh"

namespace {

void printBenchmarkState(
    const ThreadPoolBenchmarkState& state,
    std::ostream& to,
    bool printHeader = false) {
  if (printHeader) {
    to << "\n"
       << std::left << std::setw(25) << "Throughput"
        // << std::left << std::setw(25) << "overall throughput"
       << std::left << std::setw(25) << "Schedule fail rate"
       << std::left << std::setw(25) << "Requests completed"
       << "\n";
  }

  to << std::left << std::setw(25) << state.currentThroughput_
     << std::left << std::setw(25) << state.scheduleFailRate_
      // << std::left << std::setw(25) << overallThroughput
     << std::left << std::setw(25) << state.requestCompleted_
     << "\n";
}

} // namespace

int main(int argc, char* argv[]) {
  ThreadPoolBenchmark benchmark;
  benchmark.options_.numThreads_ = 48;
  benchmark.options_.queueCapacity_ = 100;

  benchmark.options_.numClientThreads_ = 1;
  benchmark.options_.singleExecutionLatency_ = 20;
  benchmark.options_.qps_ = 2000;

  benchmark.start();

  double interval = 0.5;
  int headerInterval = 10, count = 0;
  while (true) {
    std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(interval * 1000000)));
    bool printHeader = headerInterval <= 0 ? false : (count % headerInterval == 0);
    printBenchmarkState(benchmark.getState(), std::cout, printHeader);
    ++count;
  }

  return 0;
}
