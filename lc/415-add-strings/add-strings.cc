#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

class Solution {
 public:
  string addStrings(string num1, string num2) {
    int m = num1.size(), n = num2.size();

    int i1 = m - 1, i2 = n - 1, carry = 0;
    string res;
    while (i1 >= 0 || i2 >= 0 || carry > 0) {
      int d1 = i1 >= 0 ? num1[i1] - '0' : 0;
      int d2 = i2 >= 0 ? num2[i2] - '0' : 0;
      int sum = d1 + d2 + carry;
      res += '0' + (sum % 10);
      carry = sum / 10;
      --i1;
      --i2;
    }

    reverse(res.begin(), res.end());
    return res;
  }
};

void test(string num1, string num2, string expected) {
  Solution sol;
  cout << "num1: '" << num1 << "'\n";
  cout << "num2: '" << num2 << "'\n";
  string actual = sol.addStrings(num1, num2);
  cout << "num1+num2: '" << actual << "', expected: '" << expected << "'\n\n";
  assert(actual == expected);
}

int main(int argc, char* argv[]) {
  test("", "", "");
  test("0", "0", "0");
  test("0", "", "0");
  test("", "0", "0");
  test("", "7", "7");
  test("0", "-1", "-1");
  test("45754", "879", "46633");
  test("468978909426843745754", "8799239994454536997992343545454624342334", "8799239994454536998461322454881468088088");

  return 0;
}
