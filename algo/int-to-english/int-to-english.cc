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

class Solution {
 public:
  string numberToWords(int num) {
    if (num < 0) return "";
    if (num == 0) return "Zero";

    int a = num / 1000000000, b = num / 1000000 % 1000, c = num / 1000 % 1000, d = num % 1000;
    string res;
    if (a > 0) res += n2w1To1000(a) + " Billion";
    if (b > 0) res += (res.empty() ? "" : " ") + n2w1To1000(b) + " Million";
    if (c > 0) res += (res.empty() ? "" : " ") + n2w1To1000(c) + " Thousand";
    if (d > 0) res += (res.empty() ? "" : " ") + n2w1To1000(d);
    return res;
  }

  string n2w10(int x) {
    static const vector<string> table = {
      "", "One", "Two", "Three", "Four", "Five",
      "Six", "Seven", "Eight", "Nine", "Ten"
    };
    return table[x];
  }

  string n2w11To19(int x) {
    static const vector<string> table = {
      "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
      "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };
    return table[x - 11];
  }

  // pre: x >= 1 and x <= 99
  string n2w1To99(int x) {
    if (x <= 10) return n2w10(x);
    if (x <= 19) return n2w11To19(x);

    static const vector<string> table = {
      "Twenty", "Thirty", "Forty", "Fifty",
      "Sixty", "Seventy", "Eighty", "Ninety"
    };
    int a = x / 10, b = x % 10;
    string c = table[a - 2];
    string d = n2w10(b);
    return d.empty() ? c : c + " " + d;
  }

  // pre: x >= 1 and x < 1000
  string n2w1To1000(int x) {
    if (x < 100) return n2w1To99(x);
    int a = x / 100, b = x % 100;
    string c = n2w10(a) + " Hundred";
    string d = n2w1To99(b);
    return d.empty() ? c : c + " " + d;
  }
};

void test(int x) {
  Solution sol;
  cout << "x: " << x << "\n";
  cout << sol.numberToWords(x) << "\n\n";
}

int main(int argc, char* argv[]) {

  test(0);
  test(1);
  test(4);
  test(14);
  test(214);
  test(1214);
  test(12345);
  test(1234567);
  test(200);
  test(1200000);
  test(1234567891);

  return 0;
}
