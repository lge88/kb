#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int partition(vector<int>& arr, int start, int end, int p) {
  swap(arr[p], arr[end]);
  int i = start - 1, x = arr[end];
  for (int j = start; j <= end; ++j) {
    if (arr[j] <= x) swap(arr[++i], arr[j]);
  }
  return i;
}

void quickSortRecursive(vector<int>& arr, int start, int end) {
  if (start >= end) return;
  int p = start + rand() % (end - start + 1);
  int q = partition(arr, start, end, p);
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

void quickSort(vector<int>& arr) {
  quickSortRecursive2(arr, 0, arr.size() - 1);
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
