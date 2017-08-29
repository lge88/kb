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

class Vector2D {

 public:
  Vector2D(vector<vector<int>>& vec2d): A(vec2d), i(0), j(0), prevI(-1), prevJ(-1) {
    skipEmpty();
  }

  int next() {
    int res = A[i][j];
    prevI = i;
    prevJ = j;
    j += 1;
    if (j == A[i].size()) {
      i = i + 1;
      j = 0;
      skipEmpty();
    }
    return res;
  }

  bool hasNext() {
    return i < A.size();
  }

  void remove() {
    if (prevI < 0 || prevJ < 0) throw std::runtime_error("Can only remove() once per next()");

    A[prevI].erase(A[prevI].begin() + prevJ);
    if (prevI == i) {
      j -= 1;
    }

    prevI = -1;
    prevJ = -1;
  }

 private:
  vector<vector<int>>& A;
  int i, j;
  int prevI, prevJ;
  void skipEmpty() {
    int m = A.size();
    while (i < m && A[i].empty()) {
      ++i;
    }
  }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */

int main(int argc, char* argv[]) {
  vector<vector<int> > A = {{},{1,2,3},{4,5},{},{},{6},{7,8},{},{9},{10},{}};
  Vector2D i1(A);
  cout << "test iterate and remove even number:\n";
  while (i1.hasNext()) {
    int val = i1.next();
    cout << " " << val;
    if (val % 2 == 0) {
      i1.remove();
    }
  }
  cout << "\n";

  cout << "After remove even:\n";
  Vector2D i2(A);
  while (i2.hasNext()) {
    cout << " " << i2.next();
  }
  cout << "\n";
}
