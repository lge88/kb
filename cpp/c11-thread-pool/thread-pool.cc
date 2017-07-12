#include <iostream>
#include <iomanip>

#include "ThreadPool.hh"
#include "ThreadPoolBenchmark2.hh"
// #include "ThreadPoolBenchmark.hh"

int main(int argc, char* argv[]) {
  ThreadPoolBenchmark benchmark;
  benchmark.options_.numPoolThreads_ = 4;
  benchmark.options_.queueCapacity_ = 100;
  benchmark.options_.numClientThreads_ = 1;
  // benchmark.options_.thinkTimeNanoseconds_ = 1000000;
  // benchmark.options_.thinkTimeNanoseconds_ = 1000 * 1000 * 200;
  benchmark.options_.thinkTimeNanoseconds_ = 1000 * 1000 * 5;
  // benchmark.options_.thinkTimeNanoseconds_ = 0;
  benchmark.options_.refreshIntervalMilliseconds_ = 1000;
  benchmark.options_.loadRepeat_ = 10000000;

  benchmark.start();

  double interval = 1.0;
  int headerInterval = 10, count = 0;
  while (true) {
    // std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(interval * 1000000)));
    std::this_thread::sleep_for(std::chrono::seconds(1));

    bool withHeader = headerInterval <= 0 ? false : (count % headerInterval == 0);
    benchmark.getState().writeFormatString(std::cout, withHeader);
    ++count;
  }

  return 0;
}
