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
  int firstUniqChar(string s) {
    // -1: not seen, -2: repeated, >= 0, index
    int seen[26];
    for (int i = 0; i < 26; ++i) seen[i] = -1;

    int n = s.size();
    for (int i = 0; i < n; ++i) {
      int j = s[i] - 'a';
      if (seen[j] == -1) {
        seen[j] = i;
      } else if (seen[j] == -2) {
        continue;
      } else { // >= 0
        seen[j] = -2;
      }
    }

    cout << "seen:";
    for (int i = 0; i < 26; ++i) cout << " " << seen[i];
    cout << "\n";

    int sofar = n;
    for (int i = 0; i < 26; ++i) {
      if (seen[i] >= 0) sofar = min(sofar, seen[i]);
    }
    cout << "sofar: " << sofar << "\n";
    return sofar == n ? -1 : sofar;
  }
};

void test(string s) {
  Solution sol;
  cout << "s: " << s << "\n";
  cout << "result: " << sol.firstUniqChar(s) << "\n";
}

int main(int argc, char* argv[]) {
  test("leetcode");
  return 0;
}
