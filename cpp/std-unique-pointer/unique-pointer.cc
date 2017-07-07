#include <memory>
#include <iostream>

struct A {
  int x, y;
};

int sumXY(std::unique_ptr<A> a) {
  return a->x + a->y;
}

int main(int argc, char* argv[]) {
  std::unique_ptr<A> a(new A({1, 3}));

  std::cout << "sumXY(a): " << sumXY(std::move(a)) << "\n";
  // std::cout << "sumXY(a): " << sumXY(a) << "\n";

  return 0;
}
