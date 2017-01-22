#include <iostream>
#include <string>
#include <cassert>

using namespace std;

class Solution {
 public:
  // check if s is subsequence of t.
  bool isSubsequence(string s, string t) {
    int m = s.size(), n = t.size();
    int j = 0;
    for (int i = 0; i < n && j < m; ++i) {// s[0..j-1] is subsequence of t[0..i-1]
      if (s[j] == t[i]) ++j;
    }
    return j == m;
  }
};

void test(string s, string t, bool expected) {
  Solution sol;
  cout << "s: " << s << "\n";
  cout << "t: " << t << "\n";
  bool actual = sol.isSubsequence(s, t);
  cout << "isSubsequence(s, t): " << actual << ", expected: " << expected << "\n\n";
  assert(actual == expected);
}

int main(int argc, char* argv[]) {
  test("abc", "ahbgdc", 1);
  test("axc", "ahbgdc", 0);
  return 0;
}
