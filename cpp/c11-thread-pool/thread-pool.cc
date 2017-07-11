#include <vector>
#include <iostream>
#include <iomanip>
#include <thread>

#include "ThreadPool.hh"

namespace {

int latencyMilliseconds = 20;
int qps = 250;
int numThreads = 4;
int maxQueueSize = 100;

int reportInterval = qps / 2;
int headerInterval = 5;
int thinkTime = 1000000 / qps;
int goal = qps * 10;

std::atomic<int> requestCompleted(0);
double startTime = -1.0;
double lastRecordedTime = -1.0;
int notScheduled = 0;

inline double getCurrentMilliseconds() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()).count();
}

std::mutex ioMutex;

} // namespace

struct MyTask {
  void operator() () {
    // TODO: simulate busy work for given latencyMilliseconds.
    // sleep_for won't cause CPU?
    std::this_thread::sleep_for(std::chrono::milliseconds(latencyMilliseconds));
    int count = requestCompleted++;
    if (count % reportInterval == 0) {
      double now = getCurrentMilliseconds();
      double totalElapsed = now - startTime;
      double elapsedSinceLast = now - lastRecordedTime;
      // double overallThroughput = static_cast<double>(count) / totalElapsed * 1000;
      double currentThroughput = static_cast<double>(reportInterval) / elapsedSinceLast * 1000;
      bool printHeader = count % (headerInterval * reportInterval) == 0;
      {
        std::lock_guard<std::mutex> lock(ioMutex);

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
      lastRecordedTime = now;
      notScheduled = 0;
    }
  }
};

int main(int argc, char* argv[]) {
  ThreadPool<MyTask> pool(numThreads, maxQueueSize);

  lastRecordedTime = getCurrentMilliseconds();
  startTime = lastRecordedTime;
  while (requestCompleted < goal) {
    bool scheduled = pool.schedule(MyTask());
    notScheduled += scheduled ? 0 : 1;
    std::this_thread::sleep_for(std::chrono::microseconds(thinkTime));
  }

  pool.stop();
  return 0;
}
