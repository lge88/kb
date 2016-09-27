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
  int strStr(string haystack, string needle) {
    int n = haystack.size(), m = needle.size();
    if (m == 0) return 0;

    int d = 1, q = 26;
    int h1 = 0, h2 = 0;

    d = 1;
    for (int i = 0; i < m; ++i) {
      h1 += (needle[i] - 'a') * d;
      d *= q;
    }

    d = 1;
    for (int i = 0; i < m; ++i) {
      h2 += (haystack[i] - 'a') * d;
      d *= q;
    }

    if (h1 == h2) return 0;

    for (int i = m + 1; i < n; ++i) {
      h2 = ( h2 - (haystack[i - m] - 'a') ) / q + d * (haystack[i] - 'a');
      if (h1 == h2) return i - m;
      d *= q;
    }

    return -1;
  }
};

void test(const std::string& haystack, const std::string& needle) {
  Solution sol;
  cout << "haystack: " << haystack << "\n";
  cout << "needle: " << needle << "\n";
  cout << "index: " << sol.strStr(haystack, needle) << "\n\n";
}

int main(int argc, char* argv[]) {
  test("hello world hello world", "world");
  test("aaaaaaaaaaa", "aaa");
  test("abcdfabcdgabcdx", "abcde");
  test("abababacababababaababacabacababacabab", "ababacabab");
}
