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

pair<int, int> partition(vector<int>& A, int start, int end) {
  int l = start, r = end;
  // int m = l;
  // int m = r;
  // int m = l + (r - l ) / 2;
  int m = l + rand() % (r - l + 1);
  int p = A[m];
  while (l <= r) {
    while (l <= r && A[l] < p) ++l;
    while (l <= r && A[r] > p) --r;
    if (l <= r) swap(A[l++], A[r--]);
  }
  return { l, r };
}

void quickSort(vector<int>& A, int start, int end) {
  if (start >= end) return;
  auto p = partition(A, start, end);
  quickSort(A, start, p.second);
  quickSort(A, p.first, end);
}

void quickSort(vector<int>& A) {
  quickSort(A, 0, A.size() - 1);
}

void printVec(const vector<int>& A, ostream& to) {
  for (int i = 0, n = A.size(); i < n; ++i) {
    to << (i > 0 ? ", " : "") << A[i];
  }
  to << "\n";
}

void test(vector<int> A) {
  cout << "input:\n";
  printVec(A, cout);

  quickSort(A);

  cout << "sorted:\n";
  printVec(A, cout);
  cout << "\n";
}

int main(int argc, char* argv[]) {

  test({ });
  test({ 1 });
  test({ 1, 2, 3, 4, 5, 6 });
  test({ 6, 5, 4, 3, 2, 1 });
  test({ 5, 8, 3, 4, 0, 1, 2 });


  return 0;
}
