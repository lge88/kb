#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <algorithm>
#include <limits>

using namespace std;

class Solution {
 public:
  bool isPowerOfTwo(int n) {
    if (n <= 0) return false;
    for (int i = 0; i <= 30; ++i) {
      if (n == (1 << i)) return true;
    }
    return false;
  }
};

void test(int n) {
  Solution sol;
  cout << "n: " << n << " ";
  cout << "isPowerOfTwo: " << sol.isPowerOfTwo(n) << "\n";
}

int main(int argc, char* argv[]) {
  test(0);
  test(1);
  test(2);
  test(3);
  test(9);
  test(8);
  test(16);
  test(32);
  test(33);
  test(numeric_limits<int>::max());
  test(-1);
  test(-2);
  test(-4);
  return 0;
}
