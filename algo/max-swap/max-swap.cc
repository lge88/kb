#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void printVec(const vector<int>& A) {
  cout << "[";
  for (auto x : A) cout << " " << x;
  cout << " ]\n";
}

class Solution {
 public:
  int maximumSwap(int num) {
    vector<int> digits;
    while (num > 0) {
      digits.push_back(num % 10);
      num /= 10;
    }
    reverse(digits.begin(), digits.end());
    printVec(digits);

    int n = digits.size();
    vector<int> m(n, 0);
    for (int i = n - 1; i >= 0; --i) {
      if (i + 1 == n) {
        m[i] = i;
      }
      else {
        m[i] = digits[i] > digits[m[i + 1]] ? i : m[i + 1];
      }
    }
    printVec(m);

    for (int i = 0; i < n; ++i) {
      if (digits[i] < digits[m[i]]) {
        swap(digits[i], digits[m[i]]);
        break;
      }
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
      res = res * 10 + digits[i];
    }
    return res;
  }
};

void test(int x) {
  Solution sol;
  auto res = sol.maximumSwap(x);
  cout << x << " => " << res << "\n";
}

int main(int argc, char* argv[]) {

  test(2736);

  return 0;
}
