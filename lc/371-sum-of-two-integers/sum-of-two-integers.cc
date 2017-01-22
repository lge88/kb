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
#include <bitset>

using namespace std;

class Solution {
 public:
  int getSum(int a, int b) {
    if (b == 0) return a;
    return getSum(a ^ b, (a & b) << 1);
  }
};

void test(int a, int b) {
  Solution sol;
  cout << "a: " << a << ", b: " << b << "\n";
  cout << "result: " << sol.getSum(a, b) << "\n";
}

int main(int argc, char* argv[]) {
  cout << "-3: " << bitset<8*sizeof(int)>(-3) << "\n";
  test(1, 2);
  test(5, 7);
  test(13, 2);
  test(0, 0);
  test(0, 1);
  test(1, 0);
  test(0x7ffffffe, 1);
  test(-3, 2);
  test(-3, -2);
  test(3, -2);
  test(3, -6);
  return 0;
}
