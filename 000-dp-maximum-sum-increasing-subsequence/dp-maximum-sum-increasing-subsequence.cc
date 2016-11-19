#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxSumOfIncreasingSubsequence(const vector<int>& arr) {
  int n = arr.size();
  if (n == 0) return 0;

  vector<int> F(n);
  F[0] = arr[0];
  int res = F[0];
  for (int i = 1; i < n; ++i) {
    F[i] = arr[i];
    for (int j = 0; j < i; ++j) {
      if (arr[j] < arr[i]) {
        F[i] = max(F[i], F[j] + arr[i]);
      }
    }
    res = max(res, F[i]);
  }

  return res;
}

int main(int argc, char* argv[]) {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    int N;
    cin >> N;
    vector<int> arr(N);
    for (int j = 0; j < N; ++j) {
      cin >> arr[j];
    }

    cout << maxSumOfIncreasingSubsequence(arr) << "\n";
  }

  return 0;
}
