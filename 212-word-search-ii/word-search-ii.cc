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

class Solution {
 public:

  struct TrieNode {
    TrieNode* children_[26];
    bool isTerminal_;
    TrieNode() :
        isTerminal_(false)
    {
      for (size_t i = 0; i < 26; ++i) children_[i] = NULL;
    }
  };

  class Dict {
    TrieNode* root_;

    void destroyNode(TrieNode* node) {
      if (node == NULL) return;
      for (size_t i = 0; i < 26; ++i) destroyNode(node->children_[i]);
      delete node;
    }

    void addWord(const string& word) {
      TrieNode* p = root_;
      for (string::size_type i = 0; i < word.size(); ++i) {
        char c = word[i];
        size_t offset = c - 'a';
        TrieNode* next = p->children_[offset];
        if (next == NULL) {
          next = new TrieNode();
          p->children_[offset] = next;
        }
        if (i + 1 == word.size()) next->isTerminal_ = true;
        p = next;
      }
    }

   public:
    Dict(const vector<string>& words) {
      root_ = new TrieNode();
      for (size_t i = 0; i < words.size(); ++i) addWord(words[i]);
    };

    ~Dict() {
      destroyNode(root_);
    }

    bool contains(const string& word) const {
      TrieNode* node = search(word);
      return node != NULL && node->isTerminal_;
    }

    bool hasPrefix(const string& word) const {
      return search(word) != NULL;
    }

    TrieNode* search(const string& word) const {
      TrieNode* current = root_;
      for (size_t i = 0; i < word.size(); ++i) {
        char c = word[i];
        size_t offset = c - 'a';
        TrieNode* next = current->children_[offset];
        if (next == NULL) return NULL;
        current = next;
      }
      return current;
    }

  };

  void explore(const vector<vector<char> >& board, const size_t x, const size_t y,
               const string& prefix, const Dict& dict,
               vector<vector<bool> >& visited,
               set<string>& result) {
    if (visited[x][y] == true) return;

    const string word = prefix + board[x][y];
    TrieNode* node = dict.search(word);

    if (node == NULL) return;

    if (node->isTerminal_) {
      result.insert(word);
    }

    size_t m = board.size();
    size_t n = board[0].size();
    visited[x][y] = true;
    if (x >= 1) explore(board, x - 1, y, word, dict, visited, result);
    if (x + 1 < m) explore(board, x + 1, y, word, dict, visited, result);
    if (y >= 1) explore(board, x, y - 1, word, dict, visited, result);
    if (y + 1 < n) explore(board, x, y + 1, word, dict, visited, result);
    visited[x][y] = false;
  }

  vector<string> findWords(vector<vector<char> >& board, vector<string>& words) {
    set<string> result;
    size_t m = board.size();
    if (m == 0) return vector<string>();
    size_t n = board[0].size();
    if (n == 0) return vector<string>();

    Dict dict(words);
    for (size_t i = 0; i < m; ++i) {
      for (size_t j = 0; j < n; ++j) {
        vector<vector<bool> > visited(m, vector<bool>(n, false));
        explore(board, i, j, "", dict, visited, result);
      }
    }

    return vector<string>(result.begin(), result.end());
  }
};

void testDict(const Solution::Dict& dict, const string& word) {
  std::cout << "contains '" << word << "': " << dict.contains(word) << "\n";
  std::cout << "hasPrefix '" << word << "': " << dict.hasPrefix(word) << "\n";
}

void testFindWords(vector<vector<char> >& board, vector<string>& words) {
  Solution sol;
  vector<string> result = sol.findWords(board, words);
  std::cout << "result: [ ";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << (i > 0 ? ", " : "") << result[i];
  }
  std::cout << " ]\n";
}

int main(int argc, char* argv[]) {
  {
    vector<string> words = { "oath", "pea", "eat", "rain" };
    Solution::Dict dict(words);
    testDict(dict, "oath");
    testDict(dict, "pea");
    testDict(dict, "pe");
  }

  {
    vector<vector<char> > board = {
      { 'o','a','a','n' },
      { 'e','t','a','e' },
      { 'i','h','k','r' },
      { 'i','f','l','v' }
    };
    vector<string> words = { "oath", "pea", "eat", "rain" };
    testFindWords(board, words);
  }

  {
    vector<vector<char> > board = { { 'a', 'a' } };
    vector<string> words = { "a" };
    testFindWords(board, words);
  }
  return 0;
}
