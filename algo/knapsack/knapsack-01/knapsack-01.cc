#include <iostream>
#include <iomanip>
#include <vector>
#include <tuple>

using namespace std;

template<typename T>
void displayMatrix(const vector<vector<T>>& A, int w = 4, int w0 = 5) {
  int m = A.size(), n = A[0].size();

  // Header
  for (auto j = -1; j < n; ++j) {
    if (j == -1)
      cout << setw(w0) << std::left << "[*]";
    else
      cout << setw(w) << std::left << j;
  }
  cout << "\n";

  for (auto i = 0; i < m; ++i) {
    for (auto j = -1; j < n; ++j){
      if (j == -1)
        cout << setw(w0) << std::left << ("[" + to_string(i) + "]");
      else
        cout << setw(w) << std::left << A[i][j];
    }
    cout << "\n";
  }
}

int knapsack01(int m, vector<int> A, vector<int> V) {
  int n = A.size();
  vector<int> F(m + 1, 0);
  for (int i = 0; i < n; ++i) {
    const int cost = A[i], value = V[i];
    for (int j = m; j >= cost; --j) {
      F[j] = max(F[j], F[j - cost] + value);
    }
  }
  return F[m];
}

tuple<vector<int>, int> knapsack01WithSolution(int m, vector<int> A, vector<int> V, bool trace = false) {
  vector<int> subset;

  int n = A.size();
  vector<vector<int>> F(n + 1, vector<int>(m + 1, 0));
  vector<vector<bool>> K(n + 1, vector<bool>(m + 1, false));

  for (int i = 1; i <= n; ++i) {
    const int cost = A[i - 1], value = V[i - 1];
    for (int j = m; j >= 1; --j) {
      // Can not do the following since we need to detect when item i is picked.
      // F[i][j] = max(F[i - 1][j], j - cost >= 0 ? F[i - 1][j - cost] + value : 0);
      if (j - cost >= 0 && F[i - 1][j - cost] + value > F[i - 1][j]) {
        F[i][j] = F[i - 1][j - cost] + value;
        K[i][j] = true;
      } else {
        F[i][j] = F[i - 1][j];
        K[i][j] = false;
      }
    }
  }

  int j = m;
  for (int i = n; i >= 1; --i) {
    if (K[i][j]) {
      subset.push_back(i);
      j -= A[i - 1];
    }
  }

  if (trace) {
    cout << "F:\n";
    displayMatrix(F);

    cout << "\nK:\n";
    displayMatrix(K);
  }

  return { subset, F[n][m] };
}

int main(int argc, char* argv[]) {
  int n;
  cin >> n;

  int x;
  vector<int> A, V;
  for (int i = 0; i < n; ++i) {
    cin >> x;
    A.push_back(x);
  }
  for (int i = 0; i < n; ++i) {
    cin >> x;
    V.push_back(x);
  }

  int m;
  cin >> m;

  // cout << knapsack01(m, A, V) << "\n";

  bool verbose = argc > 1 && string(argv[1]) == "-v";
  vector<int> subset;
  int maxValue;
  std::tie(subset, maxValue) = knapsack01WithSolution(m, A, V, verbose);

  cout << maxValue << "\n";

  reverse(subset.begin(), subset.end());
  for (auto i = 0; i < subset.size(); ++i) cout << (i > 0 ? " " : "") << subset[i];
  cout << '\n';

  return 0;
}
