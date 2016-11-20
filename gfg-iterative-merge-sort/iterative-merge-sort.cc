#include <iostream>
#include <vector>

using namespace std;

// merge a, b into it
template<typename Iter>
void merge(Iter a, Iter aEnd, Iter b, Iter bEnd, Iter dest) {
  while (a != aEnd && b != bEnd) {
    if (*a <= *b) *dest++ = *a++;
    else *dest++ = *b++;
  }
  while (a != aEnd) *dest++ = *a++;
  while (b != bEnd) *dest++ = *b++;
}

void mergeSortRecursive(vector<int>& arr, int start, int end) {
  if (start >= end) return;

  int mid = start + (end - start) / 2;
  mergeSortRecursive(arr, start, mid);
  mergeSortRecursive(arr, mid + 1, end);

  vector<int> a(arr.begin() + start, arr.begin() + mid + 1);
  vector<int> b(arr.begin() + mid + 1, arr.begin() + end + 1);
  merge(a.begin(), a.end(), b.begin(), b.end(), arr.begin() + start);
}

void mergeSortIterative(vector<int>& arr) {
  int n = arr.size();
  int group = 1;

  while (group < n) {
    // merge all two adjacent groups of size group
    int nextGroup = group * 2;
    for (int i = 0; i < n; i += nextGroup) {
      int aStart = i;
      int aEnd = min(aStart + group - 1, n - 1);
      int bStart = aEnd + 1;
      if (bStart == n) continue;
      int bEnd = min(bStart + group - 1, n - 1);

      vector<int> a(arr.begin() + aStart, arr.begin() + aEnd + 1);
      vector<int> b(arr.begin() + bStart, arr.begin() + bEnd + 1);
      merge(a.begin(), a.end(), b.begin(), b.end(), arr.begin() + aStart);
    }
    group = nextGroup;
  }
}

void mergeSort(vector<int>& arr) {
  mergeSortRecursive(arr, 0, arr.size() - 1);
}

int main(int argc, char* argv[]) {
  int T, N;
  cin >> T;
  while (T-- > 0) {
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; ++i) cin >> arr[i];

    // mergeSort(arr);
    mergeSortIterative(arr);
    // cout << "[ ";
    for (int i = 0; i < N; ++i) cout << (i > 0 ? " " : "") << arr[i];
    // cout << " ]";
    cout << "\n";
  }
  return 0;
}
