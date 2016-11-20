#include <iostream>
#include <vector>

using namespace std;

int mergeSortAndCountInversions(vector<int>& arr, int start, int end) {
  if (start >= end) return 0;

  int mid = start + (end - start) / 2;
  int invLeft = mergeSortAndCountInversions(arr, start, mid);
  int invRight = mergeSortAndCountInversions(arr, mid + 1, end);

  int invCross = 0;
  vector<int> a(arr.begin() + start, arr.begin() + mid + 1);
  vector<int> b(arr.begin() + mid + 1, arr.begin() + end + 1);
  // merge a, b into arr[start..end] and count invCross

  int i = 0, na = a.size(), j = 0, nb = b.size();
  int k = start;
  while (i < na && j < nb) {
    if (a[i] <= b[j]) {
      arr[k++] = a[i++];
    } else {
      // whenever select a b[j], increment the inversion count
      invCross += na - i;
      arr[k++] = b[j++];
    }
  }
  while (i < na) arr[k++] = a[i++];
  while (j < nb) arr[k++] = b[j++];
  return invLeft + invRight + invCross;
}

int countInversions(vector<int>& arr) {
  return mergeSortAndCountInversions(arr, 0, arr.size() - 1);
}

int main(int argc, char* argv[]) {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    int N;
    cin >> N;
    vector<int> arr(N);
    for (int j = 0; j < N; ++j) cin >> arr[j];
    cout << countInversions(arr) << "\n";
  }
  return 0;
}
