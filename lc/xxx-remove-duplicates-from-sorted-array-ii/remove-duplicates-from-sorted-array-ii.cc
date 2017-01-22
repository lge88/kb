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
  int removeDuplicates(int A[], int n, int occurLimit) {
    // return removeDuplicatesWithCounter(A, n, occurLimit);
    return removeDuplicatesWithOffset(A, n, occurLimit);
  }

  int removeDuplicatesWithOffset(int A[], int n, int occurLimit) {
    if (n <= 1) return n;
    int len = 1;
    for (int i = 1; i < n; ++i) {
      int j = len - occurLimit;
      if (j < 0 || A[i] != A[j]) {
        A[len++] = A[i];
      }
    }
    return len;
  }

  int removeDuplicatesWithCounter(int A[], int n, int occurLimit) {
    if (n <= 1) return n;
    int len = 1, occur = 1;
    for (int i = 1; i < n; ++i) {
      if (A[i] == A[len - 1]) {
        ++occur;
        if (occur <= occurLimit) {
          A[len] = A[len - 1];
          ++len;
        }
      } else {
        occur = 1;
        A[len++] = A[i];
      }
    }
    return len;
  }
};

void test(int A[], int n, int occurLimit, int expectedA[], int expectedLen) {
  Solution sol;
  cout << "A: [ ";
  for (int i = 0; i < n; ++i) cout << (i > 0 ? ", " : "") << A[i];
  cout << " ]\n";
  cout << "n: " << n << "\n";
  cout << "occurLimit: " << occurLimit << "\n";
  int actualLen = sol.removeDuplicates(A, n, occurLimit);
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
    int occurLimit = 1;
    int expected[] = { };
    test(A, 0, occurLimit, expected, 0);
  }
  {
    int A[] = { 1 };
    int occurLimit = 1;
    int expected[] = { 1 };
    test(A, sizeof(A)/sizeof(int), occurLimit, expected, sizeof(expected)/sizeof(int));
  }
  {
    int A[] = { 1, 2, 2, 3, 4, 4, 4, 5};
    int occurLimit = 1;
    int expected[] = { 1, 2, 3, 4, 5 };
    test(A, sizeof(A)/sizeof(int), occurLimit, expected, sizeof(expected)/sizeof(int));
  }
  {
    int A[] = { 1, 2, 2, 3, 4, 4, 4, 5};
    int occurLimit = 2;
    int expected[] = { 1, 2, 2, 3, 4, 4, 5 };
    test(A, sizeof(A)/sizeof(int), occurLimit, expected, sizeof(expected)/sizeof(int));
  }
  return 0;
}
