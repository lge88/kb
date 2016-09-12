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
  int countPrimes(int n) {
    vector<bool> chart(n, false);
    int count = 0;
    for (int i = 2; i < n; ++i) {
      if (chart[i] == true) continue;
      ++count;
      int j = i;
      while (j < n) {
        chart[j] = true;
        j += i;
      }
    }
    return count;
  }
};

void test(int n) {
  Solution sol;
  cout << "countPrimes(" << n << ") => " << sol.countPrimes(n) << "\n";
}

int main(int argc, char* argv[]) {

  test(20);// 8
  test(24);// 9

  return 0;
}
