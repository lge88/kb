#include <ctime>
#include <thread>
#include <queue>
#include <tuple>
#include <mutex>
#include <iostream>
#include <unistd.h>
#include <functional>
#include <vector>

using namespace std;

uint64_t getCurrentTime() {
  time_t seconds;
  seconds = time(NULL);
  return seconds;
}

class TaskScheduler {
 public:
  using CallBack = void (*)(void);
  using Task = tuple<uint64_t, CallBack>;

 private:
  priority_queue<Task, vector<Task>, greater<Task>> tasks;
  bool stopRequested;
  mutex mtx;

 public:
  TaskScheduler(): stopRequested(false) {}

  void schedule(uint64_t executionTime, CallBack cb) {
    lock_guard<mutex> lock(mtx);
    Task task = { executionTime, cb };
    tasks.push(task);
  }

  void loop() {
    while (!stopRequested) {
      lock_guard<mutex> lock(mtx);
      auto now = getCurrentTime();
      while (!tasks.empty() && get<0>(tasks.top()) <= now) {
        cout << "ts:" << get<0>(tasks.top()) << "\n";
        auto fn = get<1>(tasks.top());
        tasks.pop();
        fn();
      }
      sleep(1);
    }
  }

  void stop() {
    lock_guard<mutex> lock(mtx);
    stopRequested = true;
  }
};

void f1() {
  cout << "f1\n";
}

void f2() {
  cout << "f2\n";
}

void f3() {
  cout << "f3\n";
}

int main() {
  TaskScheduler sched;
  auto now = getCurrentTime();
  cout << "now: " << now << "\n";

  sched.schedule(now + 3, f1);
  sched.schedule(now + 2, f2);
  sched.schedule(now + 1, f3);

  auto t = thread([&sched]() {
      cout << "start looping\n";
      sched.loop();
      cout << "end looping\n";
    });

  sleep(5);

  sched.stop();
  t.join();
}
