#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

using namespace std;

bool canWin(const vector<int>& A, int start) {
  int n = A.size();
  if (start < 0 || start >= n) return false;
  if (A[start] == 0) return true;

  vector<bool> visited(n, false);
  queue<int> q;
  q.push(start);
  visited[start] = true;

  int dir[2] = { -1, +1 };
  while (!q.empty()) {
    int u = q.front();
    q.pop();

    int delta = A[u];
    for (int k = 0; k < 2; ++k) {
      int v = u + delta * dir[k];
      if (v >= 0 && v < n && !visited[v]) {
        if (A[v] == 0) return true;
        q.push(v);
        visited[v] = true;
      }
    }
  }

  return false;

}

void test(const vector<int>& A, int start) {

  cout << "A: [";
  for (auto x : A) cout << " " << x;
  cout << " ]\n";

  bool res = canWin(A, start);
  cout << "res: " << res << "\n";
}

int main(int argc, char* argv[]) {

  test({ 0, 2, 1, 3 }, 1);
  test({ 0, 2, 1, 1 }, 1);
  return 0;
}
