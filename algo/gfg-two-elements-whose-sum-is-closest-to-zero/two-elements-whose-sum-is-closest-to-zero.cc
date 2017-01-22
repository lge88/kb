#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pair {
  int i, j;
};

// O(n^2)
Pair findPairSumClosestToZeroBF(const vector<int>& arr) {
  Pair p;
  int n = arr.size();
  if (n < 2) throw runtime_error("arr.size() < 2");

  p.i = 0;
  p.j = 1;
  int closestSum = arr[p.i] + arr[p.j];

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int sum = arr[i]  + arr[j];
      if (abs(sum) < abs(closestSum)) {
        closestSum = sum;
        p.i = i;
        p.j = j;
      }
      if (sum == 0) break;
    }
  }

  if (arr[p.i] > arr[p.j]) swap(p.i, p.j);

  return p;
}

// O(n*log(n))
Pair findPairSumClosestToZero(vector<int>& arr) {
  Pair p;
  int n = arr.size();
  if (n < 2) throw runtime_error("arr.size() < 2");

  sort(arr.begin(), arr.end());
  p.i = 0;
  p.j = arr.size() - 1;
  int closestSum = arr[p.i] + arr[p.j];

  int i = p.i, j = p.j;
  while (i < j) {
    int sum = arr[i]  + arr[j];
    if (abs(sum) < abs(closestSum)) {
      closestSum = sum;
      p.i = i;
      p.j = j;
    }
    if (sum == 0) break;
    if (sum > 0) {
      --j;
    } else {
      ++i;
    }
  }

  if (arr[p.i] > arr[p.j]) swap(p.i, p.j);

  return p;
}

int main(int argc, char* argv[]) {
  int T, N;
  cin >> T;
  while (T-- > 0) {
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; ++i) cin >> arr[i];

    // Pair p = findPairSumClosestToZeroBF(arr);
    Pair p = findPairSumClosestToZero(arr);
    cout << arr[p.i] << " " << arr[p.j] << "\n";
  }
  return 0;
}
