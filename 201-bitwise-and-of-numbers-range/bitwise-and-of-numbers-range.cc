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

using namespace std;

class Solution {
 public:
  int rangeBitwiseAnd(int m, int n) {
    int count = 0;
    while (m != n) {
      m = m >> 1;
      n = n >> 1;
      ++count;
    }
    while (count-- > 0) {
      m = m << 1;
    }
    return m;
  }
};

int main(int argc, char* argv[]) {
  Solution sol;
  int m = 5, n = 7;
  cout << "m:" << m << ", n: " << n << ", result: " << sol.rangeBitwiseAnd(m, n) << "\n";
  return 0;
}
