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

using namespace std;
class Solution {
 public:
  struct TrieNode {
    bool valid;
    TrieNode* children[26];
    TrieNode(): valid(false) {
      fill(begin(children), end(children), nullptr);
    }
  };

  void insert(TrieNode* root, const string& word) {
    TrieNode* p = root;
    for (auto c : word) {
      int i = c - 'a';
      if (p->children[i] == nullptr) {
        p->children[i] = new TrieNode();
      }
      p = p->children[i];
    }
    p->valid = true;
  }

  TrieNode* buildTrie(const vector<string>& words) {
    auto root = new TrieNode();
    for (const auto& word : words) {
      insert(root, word);
    }
    return root;
  }

  int boggleGame(vector<vector<char>> &board, vector<string> &words) {
    if (board.empty() || board[0].empty()) return {};

    TrieNode* root = buildTrie(words);
    int m = board.size(), n = board[0].size();
    vector<string> longestCol;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<string> collection;
        dfs(board, i, j, root, visited, collection, longestCol);
      }
    }

    cout << "longestCol:[";
    for (auto x : longestCol) {
      cout << " " << x;
    }
    cout << " ]\n";
    return longestCol.size();
  }

  using Path = vector<pair<int, int>>;
  void findAllPaths(const vector<vector<char>>& board, int i, int j,
                    TrieNode* cur,
                    vector<vector<bool>>& visited,
                    Path& path,
                    vector<Path>& res) {
    int m = board.size(), n = board[0].size();
    char c = board[i][j];
    int idx = c - 'a';
    if (cur->children[idx] == nullptr) return;

    TrieNode* next = cur->children[idx];
    visited[i][j] = true;
    path.push_back({ i, j });

    if (next->valid) {
      // If we found a word, keep searching won't help to get move words in the collection.
      // So we can stop here.
      res.push_back(path);
    }
    else {
      static const int di[4] = { -1, +1, +0, +0 };
      static const int dj[4] = { +0, +0, -1, +1 };
      for (int k = 0; k < 4; ++k) {
        int ii = i + di[k], jj = j + dj[k];
        if (ii >= 0 && ii < m && jj >= 0 && jj < n && !visited[ii][jj]) {
          findAllPaths(board, ii, jj, next, visited, path, res);
        }
      }
    }

    visited[i][j] = false;
    path.pop_back();
  }

  // pre:
  // 1) root is not null
  // 2) i, j is within board
  // 3) visited[i][j] is false
  void dfs(const vector<vector<char>>& board, int i, int j,
           TrieNode* root,
           vector<vector<bool>>& visited,
           vector<string>& collection,
           vector<string>& longestCol) {
    vector<Path> paths;
    Path path;
    findAllPaths(board, i, j, root, visited, path, paths);
    if (paths.empty()) return;

    int m = board.size(), n = board[0].size();
    for (auto points : paths) {
      string word;
      for (auto p : points) {
        visited[p.first][p.second] = true;
        word += board[p.first][p.second];
      }
      collection.push_back(word);
      if (collection.size() > longestCol.size()) {
        longestCol = collection;
      }

      for (int k = i * n + j + 1, l = m * n; k < l; ++k) {
        int x = k / n, y = k % n;
        if (visited[x][y]) continue;
        dfs(board, x, y, root, visited, collection, longestCol);
      }

      for (auto p : points) visited[p.first][p.second] = false;
      collection.pop_back();
    }
  }
};

void test(vector<string> board, vector<string> words) {
  Solution sol;
  vector<vector<char>> internalBoard;
  for (auto row : board) {
    internalBoard.push_back({});
    for (auto col : row) {
      internalBoard.back().push_back(col);
    }
  }
  cout << "res: " << sol.boggleGame(internalBoard, words) << "\n";
}

int main(int argc, char* argv[]) {
  {
    vector<string> board = { "abcdefg", "huyuyww", "ghihjui", "wuiiuww" };
    vector<string> words = {"efg","defi","gh","iuw","ww","iw","ghih","dasf","aaa"};
    test(board, words);
  }

  {
    vector<string> board = { "aaaa", "aaaa", "aaaa" };
    vector<string> words = {"aaa","aa","a","aaaa","aaaaa","aaaaaa"};
    test(board, words);
  }

  {
    vector<string> board = { "aa", "aa" };
    vector<string> words = {"a","aa","aaa","aaaa", "aaaaa" };
    test(board, words);
  }

  return 0;
}
