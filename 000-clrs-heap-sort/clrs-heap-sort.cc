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

using namespace std;

inline int parent(int i) { return (i - 1) / 2; }
inline int left(int i) { return i * 2 + 1; }
inline int right(int i) { return i * 2 + 2; }

void maxHeapify(vector<int>& A, int i, int n) {
  int l = left(i);
  if (l >= n) return;

  int largest = i;
  if (A[l] > A[i]) largest = l;

  int r = right(i);
  if (r < n && A[r] > A[largest]) largest = r;

  if (largest != i) {
    swap(A[largest], A[i]);
    maxHeapify(A, largest, n);
  }
}

void buildMaxHeap(vector<int>& A, int n) {
  for (int i = n / 2 - 1; i >= 0; --i) {
    maxHeapify(A, i, n);
  }
}

void heapSort(vector<int>& A) {
  buildMaxHeap(A, A.size());
  int i = A.size();
  while (i >= 2) {
    swap(A[0], A[i - 1]);
    i--;
    maxHeapify(A, 0, i);
  }
}

void test(vector<int>& A) {
  vector<int> Acopy = A;

  cout << "A: [ ";
  for (auto x : A) cout << x << " ";
  cout << "]\n";

  buildMaxHeap(A, A.size());

  cout << "Max heap:\n";
  for (auto x : A) cout << x << " ";
  cout << "\n";

  heapSort(Acopy);
  cout << "Sorted: \n";
  for (auto x : Acopy) cout << x << " ";
  cout << "\n\n";
}

int main(int argc, char* argv[]) {
  {
    vector<int> A = { 1, 0, 3, 6, 7, 4, 15, 8, 10, 2 };
    test(A);
  }
  return 0;
}
