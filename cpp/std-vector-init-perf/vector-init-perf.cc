#include <iostream>
#include <vector>
#include "Timer.hh"
#include <boost/shared_array.hpp>

using namespace std;

#define ARRAY_SIZE 5000

struct S1 {
  int array[ARRAY_SIZE];
};

struct S2 {
  boost::shared_array<int> array;
  S2()
      :
      array(new int[ARRAY_SIZE])
  {}
};

struct S3 {
  int* array;
  S3()
      :
      array(new int[ARRAY_SIZE])
  {}
};

template<typename T>
void benchmark(const std::string& name) {
  Timer timer;
  timer.start();

  size_t repeat = 1000;
  for (size_t i = 0; i < repeat; ++i) {
    std::vector<T> objects(1000);
  }

  timer.getDeltaUs();
  std::cout << name << ", avg: " <<  (double)timer.getDeltaUs()/(double)repeat << " us\n";
}

int main(int argc, char* argv[]) {
  benchmark<S1>("array");
  benchmark<S2>("boost::shared_array");
  benchmark<S3>("array pointer");
  return 0;
}
