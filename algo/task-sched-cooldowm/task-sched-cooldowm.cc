#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <array>

using namespace std;

string sched(const string& s, int k) {
  // last seen index
  array<int, 256> idx;
  fill(begin(idx), end(idx), -1);

  string t;
  for (auto c : s) {
    int cur = t.size();
    int last = idx[c];
    if (last != -1) {
      int spaces = cur - last - 1;
      int paddings = k - spaces;
      if (paddings > 0) {
        t += string(paddings, '_');
      }
    }
    // The actual index after padding
    cur = t.size();
    t += c;
    idx[c] = cur;
  }
  return t;
}

void test(const string& s, int k) {
  cout << "[in ]: " << s << "\n";
  cout << "[out]: " << sched(s, k) << "\n";
}

int main(int argc, char* argv[]) {
  test("AABACCDCD", 3);
  test("CDCD", 3);
}
