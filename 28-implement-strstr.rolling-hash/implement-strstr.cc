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
  // Computes a^b mod n
  // clrs
  // int modExp(int a, int b, int n) {
  //   // int c = 0;
  //   int d = 1;
  //   for (int i = 31; i >= 0; --i) {
  //     // c *= 2;
  //     d = (d * d) % n;
  //     if (b & (1 << i))  {
  //       // c += 1;
  //       d = (d * a) % n;
  //     }
  //   }
  //   return d;
  // }

  // Recursive
  int modExp(int a, int b, int n) {
    if (b == 0) return 1;
    int partial = modExp(a, b / 2, n);
    int result = (partial * partial) % n;
    if ((b % 2) == 0) return result;
    result *= a % n;
    return result % n;
  }

  int strStr(string haystack, string needle) {
    int m = needle.size(), n = haystack.size();
    if (m == 0) return 0;
    if (m > n) return -1;

    int d = 26;
    int q = 31;
    int h = modExp(d, m - 1, q);
    int p = 0;
    int t = 0;

    for (int i = 0; i < m; ++i) {
      int Pi = needle[i] - 'a';
      int Ti = haystack[i] - 'a';
      p = (d * p + Pi) % q;
      t = (d * t + Ti) % q;
    }

    // cout << "\np: " << p << "\n";
    // cout << "t0: " << t << "\n";

    for (int s = 0; s <= n - m; ++s) {
      if (p == t) {
        if (needle == haystack.substr(s, m)) {
          return s;
        }
      }

      if (s < n - m) {
        int Ts = haystack[s] - 'a';
        int Tsm = haystack[s + m] - 'a';
        t = (((d * (t - (Ts * h) % q) % q) %q + Tsm % q) % q + q) % q;
        // cout << "t" << s << ": " << t << "\n";
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

void testModExp(int a, int b, int n) {
  Solution sol;
  cout << "a: " << a << " b: " << b << " n: " << n << " modExp: " << sol.modExp(a, b, n) << "\n";
}

int main(int argc, char* argv[]) {
  testModExp(4, 13, 497);
  testModExp(7, 560, 561);
  testModExp(26, 5, 31);

  test("hello world hello world", "world");
  test("aaaaaaaaaaa", "aaa");
  test("abcdfabcdgabcdx", "abcde");
  test("abababacababababaababacabacababacabab", "ababacabab");
}
