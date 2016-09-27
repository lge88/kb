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

    int k;
    // build prefix function
    vector<int> s(m, 0);
    k = 0;
    for (int i = 1; i < m; ++i) {
      while (k > 0 && needle[k] != needle[i]) {
        k = s[k - 1];
      }

      if (needle[k] == needle[i]) {
        k += 1;
      }

      s[i] = k;
    }

    k = 0;
    for (int i = 0; i < n; ++i) {
      while (k > 0 && needle[k] != haystack[i]) {
        k = s[k - 1];
      }
      if (needle[k] == haystack[i]) {
        k += 1;
      }
      if (k == m) {
        return i - k + 1;
      }
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
