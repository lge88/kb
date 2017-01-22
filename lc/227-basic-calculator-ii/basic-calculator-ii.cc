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
#include <stack>

using namespace std;

class Solution {
 public:
  int calculate(string s) {
    // Current operator
    char op = '+';
    stack<int> nums;
    int n = s.size();
    for (size_t i = 0; i < n; ++i) {
      char c = s[i];

      // Skip white space
      if (c == ' ') {
        continue;
      }
      // operator
      else if (c == '+' || c == '-' || c == '*' || c == '/') {
        op = c;
      }
      // Parse number
      else if (c >= '0' && c <= '9') {
        int num = c - '0';
        int j = i + 1;
        while (j < n && s[j] >= '0' && s[j] <= '9') {
          num = 10 * num + (s[j] - '0');
          ++j;
        }
        i = j - 1;
        if (op == '+') {
          nums.push(num);
        }
        else if (op == '-') {
          nums.push(-num);
          op = '+';
        }
        else if (op == '*') {
          int a = nums.top();
          nums.pop();
          nums.push(a * num);
          op = '+';
        }
        else if (op == '/') {
          int a = nums.top();
          nums.pop();
          nums.push(a / num);
          op = '+';
        }
        else {
          throw runtime_error("Unknown operator " + string(1, c));
        }
      }
      else {
        throw runtime_error("Unknown char " + string(1, c));
      }
    }

    int res = 0;
    while (!nums.empty()) {
      res += nums.top();
      nums.pop();
    }

    return res;
  }
};

void test(const string& s, int expected) {
  Solution sol;
  cout << "s: \"" << s << "\"\n";
  cout << "result: " << sol.calculate(s) << "\n";
  cout << "expected: " << expected << "\n\n";
}

int main(int argc, char* argv[]) {
  test("3+2*2", 7);
  test("3-1*2", 1);
  test(" 3/2 ", 1);
  test(" 3+5 / 2 ", 5);
  return 0;
}
