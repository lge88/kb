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

class Matrix {
 public:
  const int m, n;
  Matrix(int aM, int aN): m(aM), n(aN), data(m * n, 0) {}
  int& operator() (int i, int j) { return data[k(i, j)]; }
 private:
  vector<int> data;
  int k(int i, int j) { return i * n + j; }
};

void printMatrix(Matrix& A, ostream& to) {
  for (int i = 0; i < A.m; ++i) {
    for (int j = 0; j < A.n; ++j) {
      to << (j > 0 ? "," : "") << A(i, j);
    }
    to << "\n";
  }
}

namespace {

bool isFirst = true;

void output(int x, ostream& to) {
  to << (isFirst ? "" : ",") << x;
  isFirst = false;
}

// 1 --> 2
// ^     |
// |     V
// 4 <-- 3
void printRect(
    Matrix& A,
    int i1, int j1, // int i2, int j2,
    int i3, int j3, // int i4, int j4,
    ostream& to) {
  if (i1 > i3 || j1 > j3) return;
  // i1 <= i3 && j1 <= j3
  if (i1 == i3) {
    for (int j = j1; j <= j3; ++j) {
      output(A(i1, j), to);
    }
  }
  else if (j1 == j3) {
    for (int i = i1; i <= i3; ++i) {
      output(A(i, j1), to);
    }
  }
  else {
    // top border
    for (int j = j1; j < j3; ++j) {
      output(A(i1, j), to);
    }
    // right border
    for (int i = i1; i < i3; ++i) {
      output(A(i, j3), to);
    }
    // bottom border
    for (int j = j3; j > j1; --j) {
      output(A(i3, j), to);
    }
    // left border
    for (int i = i3; i > i1; --i) {
      output(A(i, j1), to);
    }
  }
}

} // namespace

void spiralPrintMatrix(Matrix& A, ostream& to) {
  isFirst = true;
  int i1 = 0, j1 = 0, i3 = A.m - 1, j3 = A.n - 1;
  while (i1 <= i3 && j1 <= j3) {
    printRect(A, i1, j1, i3, j3, to);
    i1 += 1;
    j1 += 1;
    i3 -= 1;
    j3 -= 1;
  }

}

int main(int argc, char* argv[]) {
  int m, n;
  string word;
  getline(cin, word, ',');
  m = stoi(word);

  getline(cin, word);
  n = stoi(word);

  Matrix A(m, n);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j == n - 1) {
        getline(cin, word);
      } else {
        getline(cin, word, ',');
      }
      A(i, j) = stoi(word);
    }
  }

  // cout << "A:\n";
  // printMatrix(A, cout);
  spiralPrintMatrix(A, cout);

  return 0;
}
