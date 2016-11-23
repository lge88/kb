#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int partition(vector<int>& arr, int start, int end) {
  int q = start - 1, x = arr[end];
  for (int i = start; i <= end; ++i) {
    if (arr[i] <= x) swap(arr[++q], arr[i]);
  }
  return q;
}

void quickSortRecursive(vector<int>& arr, int start, int end) {
  if (start >= end) return;
  // swap(arr[start + rand() % (end - start + 1)], arr[end]);
  int q = partition(arr, start, end);
  quickSortRecursive(arr, start, q - 1);
  quickSortRecursive(arr, q + 1, end);
}

void quickSortRecursive2(vector<int>& arr, int start, int end) {
  if (start >= end) return;
  // swap(arr[start + rand() % (end - start + 1)], arr[end]);
  int q = start - 1, x = arr[end];
  for (int i = start; i <= end; ++i) {
    if (arr[i] <= x) swap(arr[++q], arr[i]);
  }
  quickSortRecursive2(arr, start, q - 1);
  quickSortRecursive2(arr, q + 1, end);
}

struct Range {
  int start_, end_;
  Range(int start, int end): start_(start), end_(end) {}
};

void quickSortIterative(vector<int>& arr) {
  int n = arr.size();
  if (n <= 1) return;

  vector<Range> stk;
  stk.push_back(Range(0, n - 1));
  while (!stk.empty()) {
    int start = stk.back().start_, end = stk.back().end_;
    stk.pop_back();
    // swap(arr[start + rand() % (end - start + 1)], arr[end]);
    int q = partition(arr, start, end);
    if (start < q - 1) stk.push_back(Range(start, q - 1));
    if (q + 1 < end) stk.push_back(Range(q + 1, end));
  }
}

void quickSort(vector<int>& arr) {
  // quickSortRecursive(arr, 0, arr.size() - 1);
  // quickSortRecursive2(arr, 0, arr.size() - 1);
  quickSortIterative(arr);
}

int main(int argc, char* argv[]) {
  int T, N;
  cin >> T;
  while (T-- > 0) {
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; ++i) cin >> arr[i];
    quickSort(arr);
    for (int i = 0; i < arr.size(); ++i) cout << (i > 0 ? " " : "") << arr[i];
    cout << "\n";
  }
  return 0;
}
