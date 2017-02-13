#ifndef __TIMER_HH__
#define __TIMER_HH__

#include <sys/time.h>
#include <stdint.h>

class Timer {
  timeval started_;

 public:
  Timer() {
    started_.tv_sec = 0;
    started_.tv_usec = 0;
  }

  inline void start() {
    gettimeofday(&started_, NULL);
  }

  inline uint64_t getDeltaMs() const {
    timeval now, delta;
    gettimeofday(&now, NULL);
    timersub(&now, &started_, &delta);
    return delta.tv_sec * 1000 + delta.tv_usec / 1000;
  }

  inline uint64_t getDeltaUs() const {
    timeval now, delta;
    gettimeofday(&now, NULL);
    timersub(&now, &started_, &delta);
    return delta.tv_sec * 1000000 + delta.tv_usec;
  }
};

#endif // __TIMER_HH__
