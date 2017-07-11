#include <iostream>
#include <boost/thread.hpp>

int main(int argc, char* argv[]) {

  std::cout << "hardware_concurrency: " << boost::thread::hardware_concurrency() << "\n";

  return 0;
}
