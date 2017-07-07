#include <iostream>
#include <vector>
#include <boost/shared_array.hpp>
#include <boost/scoped_array.hpp>
#include <boost/noncopyable.hpp>

struct B {
  int x, y;
};

struct A {
  boost::shared_array<B> arr_;
  A(): arr_(new B[2]) {
    std::cout << "called A()\n";
  }
  // A(const A& other)  {
  //   std::cout << "called A(const A& other)\n";
  // }
};

struct C {
  std::vector<A> aList_;
  C(size_t n): aList_(n) {}
};


int main(int argc, char* argv[]) {
  C c(3);
  for (size_t i = 0; i < 3; ++i) {
    c.aList_[i].arr_[0].x = i + 1000;
    c.aList_[i].arr_[0].y = i + 2000;
    c.aList_[i].arr_[1].x = i + 4000;
    c.aList_[i].arr_[1].y = i + 5000;
  }

  for (size_t i = 0; i < 3; ++i) {
    std::cout << "c.aList_[" << i << "]: " <<
        "address of arr_: " << c.aList_[i].arr_.get() << ", "
        "(" << c.aList_[i].arr_[0].x << ", " << c.aList_[i].arr_[0].y << "), " <<
        "(" << c.aList_[i].arr_[1].x << ", " << c.aList_[i].arr_[1].y << "), " <<
        "\n";
  }

  return 0;
}
