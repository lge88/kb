#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

class Solution {
 public:
  string multiply(string num1, string num2) {
    int m = num1.size(), n = num2.size();
    vector<int> r(m + n, 0);
    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        int k1 = i + j;
        int k2 = i + j + 1;
        int d1 = num1[i] - '0';
        int d2 = num2[j] - '0';
        int sum = r[k2] + d1 * d2;
        r[k2] = sum % 10;
        r[k1] += sum / 10;
      }
    }

    string res;
    for (int i = 0, len = r.size(); i < len; ++i) {
      if (res.size() == 0 && r[i] == 0) continue;
      res += '0' + r[i];
    }
    if (res.size() == 0) res += '0';

    return res;
  }
};

void test(string num1, string num2, string expected) {
  Solution sol;
  cout << "num1: '" << num1 << "'\n";
  cout << "num2: '" << num2 << "'\n";
  string actual = sol.multiply(num1, num2);
  cout << "num1+num2: '" << actual << "', expected: '" << expected << "'\n\n";
  assert(actual == expected);
}

int main(int argc, char* argv[]) {
  test("0", "0", "0");
  test("4", "0", "0");
  test("0", "8", "0");
  test("8", "1", "8");
  test("1", "9", "9");
  test("9133", "0", "0");
  test("45754", "879", "40217766");
  test("468978909426843745754", "8799239994454536997992343545454624342334", "4126657976384355370439965226583331929827298448728793354949836");

  return 0;
}
