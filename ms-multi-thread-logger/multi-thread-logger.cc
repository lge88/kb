#include <iostream>
#include <thread>

#include "Logger.hh"

using namespace std;

namespace {

mutex coutMutex;

} // namespace

void doAppend(Logger& logger, const string& tag, int i) {
  uint64_t s = logger.append(i);
  {
    lock_guard<mutex> lock(coutMutex);
    cerr << tag << "\t" << i << "\t" << s << "\n";
  }
}

void doAppendRange(Logger& logger, const string& tag, int from, int to) {
  for (int i = from; i <= to; ++i) doAppend(logger, tag, i);
}

void doRead(const Logger& logger, const string& tag, int i) {
  uint64_t s = static_cast<uint64_t>(i);
  int v = logger.read(s);
  {
    lock_guard<mutex> lock(coutMutex);
    cerr << tag << "\t" << s << "\t" << v << "\n";
  }
}

void doRandomRead(const Logger& logger, const string& tag, int from, int to) {
  int i = from + rand() % (to - from + 1);
  doRead(logger, tag, i);
}

void doRandomReadNTimes(const Logger& logger, const string& tag, int from, int to, int N) {
  for (int i = 0; i < N; ++i) doRandomRead(logger, tag, from, to);
}

void doTruncate(Logger& logger, const string& tag, int N) {
  uint64_t s = static_cast<uint64_t>(N);
  logger.truncate(s);
  {
    lock_guard<mutex> lock(coutMutex);
    cerr << tag << "\t" << s << "\n";
  }
}

void testSingleThread() {
  Logger logger;
  doAppendRange(logger, "APPEND", 0, 10);
  for (int i = 0; i <= 10; ++i) doRead(logger, "READ", i);
  doTruncate(logger,"TRUNCATE", 5);
  for (int i = 0; i <= 10; ++i) doRead(logger, "READ", i);
}

void testOneAppendOneRead() {
  Logger logger;

  vector<thread> threads;
  threads.push_back(thread(doAppendRange, ref(logger), "A1", 0, 10));
  threads.push_back(thread(doAppendRange, ref(logger), "A2", 0, 10));
  threads.push_back(thread(doRandomReadNTimes, ref(logger), "R1", 5, 5, 10));
  threads.push_back(thread(doRandomReadNTimes, ref(logger), "R2", 5, 5, 10));
  threads.push_back(thread(doTruncate, ref(logger), "T1", 2));

  for (thread& t: threads) t.join();
}

int main(int argc, char* argv[]) {
  srand(0);
  // testSingleThread();
  testOneAppendOneRead();
  return 0;
}
