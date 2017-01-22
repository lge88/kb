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

  int next(int n) {
    int res = 0;
    while (n != 0) {
      int digit = n % 10;
      res += digit * digit;
      n /= 10;
    }
    return res;
  }

  bool isHappy(int n) {
    unordered_set<int> visited;
    visited.insert(n);

    while (n != 1) {
      n = next(n);
      cout << "n: " << n << "\n";

      if (n == 1) return true;
      if (visited.find(n) != visited.end()) return false;
      visited.insert(n);
    }
    return true;
  }

};

void test(int n) {
  Solution sol;
  cout << n << " is happy number: " << sol.isHappy(n) << "\n";
}

int main(int argc, char* argv[]) {
  test(19);
  return 0;
}
