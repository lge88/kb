#include <iostream>
#include <iomanip>

#include "ThreadPool.hh"
#include "ThreadPoolBenchmark2.hh"
// #include "ThreadPoolBenchmark.hh"

int main(int argc, char* argv[]) {
  ThreadPoolBenchmark benchmark;
  benchmark.options_.numPoolThreads_ = 2;
  benchmark.options_.queueCapacity_ = 100;

  benchmark.options_.numClientThreads_ = 2;
  benchmark.options_.refreshIntervalMilliseconds_ = 100;
  // benchmark.options_.singleExecutionLatency_ = 0;
  // benchmark.options_.qps_ = 12000;
  // benchmark.options_.qps_ = 0;

  benchmark.start();

  double interval = 1.0;
  int headerInterval = 10, count = 0;
  while (true) {
    // std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(interval * 1000000)));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ThreadPoolBenchmarkState state = benchmark.getState();

    bool withHeader = headerInterval <= 0 ? false : (count % headerInterval == 0);
    state.writeFormatString(std::cout, withHeader);
    ++count;
  }

  return 0;
}
