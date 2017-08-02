#include <iostream>
#include <unordered_map>

using namespace std;

template <typename T> class TD;

int main(int argc, char* argv[]) {
  unordered_map<int, int> m = {
    { 1, 2 },
    { 2, 4 },
    { 3, 6 },
  };

  auto it = m.find(1);
  TD<decltype(it)> x;

  return 0;
}
