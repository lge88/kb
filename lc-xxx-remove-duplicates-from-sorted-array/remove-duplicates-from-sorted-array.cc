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
#include <cassert>

using namespace std;

class Solution {
 public:
  int removeDuplicates(int A[], int n) {
    // return unique(A, A + n) - A;
    if (n <= 1) return n;
    int len = 1;
    for (int i = 2; i < n; ++i) {
      if (A[i] != A[len - 1]) {
        A[len] = A[i];
        ++len;
      }
    }
    return len;
  }
};

void test(int A[], int n, int expectedA[], int expectedLen) {
  Solution sol;
  cout << "A: [ ";
  for (int i = 0; i < n; ++i) cout << (i > 0 ? ", " : "") << A[i];
  cout << " ]\n";
  cout << "n: " << n << "\n";
  int actualLen = sol.removeDuplicates(A, n);
  cout << "removeDuplicates(A, n):\n";
  cout << "actualLen: " << actualLen << ", expectedLen: " << expectedLen << "\n";
  cout << "actualA: [ ";
  for (int i = 0; i < actualLen; ++i) cout << (i > 0 ? ", " : "") << A[i];
  cout << " ]\n";
  cout << "expectedA: [ ";
  for (int i = 0; i < expectedLen; ++i) cout << (i > 0 ? ", " : "") << expectedA[i];
  cout << " ]\n\n";
  assert(actualLen == expectedLen);
  assert(vector<int>(A, A + actualLen) == vector<int>(expectedA, expectedA + expectedLen));
}

int main(int argc, char* argv[]) {
  {
    int A[] = { };
    int expected[] = { };
    test(A, 0, expected, 0);
  }
  {
    int A[] = { 1 };
    int expected[] = { 1 };
    test(A, sizeof(A)/sizeof(int), expected, sizeof(expected)/sizeof(int));
  }
  {
    int A[] = { 1, 2, 2, 3, 4, 4, 4, 5};
    int expected[] = { 1, 2, 3, 4, 5 };
    test(A, sizeof(A)/sizeof(int), expected, sizeof(expected)/sizeof(int));
  }
  return 0;
}
