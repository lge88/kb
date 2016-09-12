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

class TrieNode {
 public:
  bool isTerminal_;
  TrieNode* children_[26];
  TrieNode() :
      isTerminal_(false)
  {
    fill_n(&children_[0], 26, static_cast<TrieNode*>(NULL));
  }
};

class Trie {
 public:
  Trie() {
    root = new TrieNode();
  }

  void destroyNode(TrieNode* node) {
    if (node == NULL) return;
    for (size_t i = 0; i < 26; ++i) destroyNode(node->children_[i]);
    delete node;
  }

  ~Trie() {
    destroyNode(root);
  }

  // Inserts a word into the trie.
  void insert(string word) {
    TrieNode* p = root;
    for (size_t i = 0; i < word.size(); ++i) {
      char c = word[i];
      size_t offset = c - 'a';
      TrieNode* next = p->children_[offset];
      if (next == NULL) {
        next = new TrieNode();
        p->children_[offset] = next;
      }
      // last char
      if (i + 1 == word.size()) {
        next->isTerminal_ = true;
      }

      p = next;
    }
    return;
  }

  // Returns if the word is in the trie.
  bool search(string word) {
    TrieNode* p = root;
    for (size_t i = 0; i < word.size(); ++i) {
      char c = word[i];
      size_t offset = c - 'a';
      TrieNode* next = p->children_[offset];
      if (next == NULL) {
        return false;
      }
      // last char
      if (i + 1 == word.size()) {
        return next->isTerminal_;
      }
      p = next;
    }
    // For case word.size() == 0
    return true;
  }

  // Returns if there is any word in the trie
  // that starts with the given prefix.
  bool startsWith(string prefix) {
    TrieNode* p = root;
    for (size_t i = 0; i < prefix.size(); ++i) {
      char c = prefix[i];
      size_t offset = c - 'a';
      TrieNode* next = p->children_[offset];
      if (next == NULL) {
        return false;
      }
      p = next;
    }
    // For case word.size() == 0
    return true;
  }

 private:
  TrieNode* root;
};

void test(Trie& trie, const string& key) {
  std::cout << "search '" << key << "': " << trie.search(key) << "\n";
  std::cout << "startsWith '" << key << "': " << trie.startsWith(key) << "\n";
}

int main(int argc, char* argv[]) {
  {
    Trie trie;
    trie.insert("hello");
    trie.insert("word");
    trie.insert("foo");
    trie.insert("food");
    test(trie, "hello");
    test(trie, "hell");
    test(trie, "foo");
    test(trie, "food");
  }

  return 0;
}
