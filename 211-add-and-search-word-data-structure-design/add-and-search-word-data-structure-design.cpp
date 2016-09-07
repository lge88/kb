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

class WordDictionary {
  struct TrieNode {
    bool isTerminal_;
    TrieNode* children_[26];
    TrieNode() :
        isTerminal_(false)
    {
      for (size_t i = 0; i < 26; ++i) children_[i] = NULL;
    }
  };

  TrieNode* root;

  void destroyNode(TrieNode* node) {
    if (node == NULL) return;
    for (size_t i = 0; i < 26; ++i) destroyNode(node->children_[i]);
    delete node;
  }

 public:

  WordDictionary() {
    root = new TrieNode();
  }

  ~WordDictionary() {
    destroyNode(root);
  }

  // Adds a word into the data structure.
  void addWord(string word) {
    TrieNode* p = root;
    for (string::size_type i = 0; i < word.size(); ++i) {
      char c = word[i];
      size_t offset = c - 'a';
      TrieNode* next = p->children_[offset];
      if (next == NULL) {
        next = new TrieNode();
        p->children_[offset] = next;
      }

      if (i + 1 == word.size()) {
        next->isTerminal_ = true;
      }

      p = next;
    }
  }

  bool searchHelper(const string& word, const string::size_type& i, TrieNode* p) {
    char c = word[i];
    if (c != '.') {
      size_t offset = c - 'a';
      TrieNode* next = p->children_[offset];
      if (next == NULL) return false;
      if (i + 1 == word.size()) return next->isTerminal_;
      return searchHelper(word, i + 1, next);
    } else {
      for (size_t j = 0; j < 26; ++j) {
        TrieNode* next = p->children_[j];
        if (next == NULL) continue;
        if (i + 1 == word.size()) {
          if (next->isTerminal_) return true;
        } else {
          if (searchHelper(word, i + 1, next)) return true;
        }
      }
      return false;
    }
  }

  // Returns if the word is in the data structure. A word could
  // contain the dot character '.' to represent any one letter.
  bool search(string word) {
    if (word.size() == 0) return false;
    return searchHelper(word, 0, root);
  }
};

void cmdAdd(WordDictionary& wd, const string& word) {
  std::cout << "Add " << word << "\n";
  wd.addWord(word);
}

void test(WordDictionary& wd, const string& word) {
  std::cout << "saerch " << word << ": " << wd.search(word) << "\n";
}

int main(int argc, char* argv[]) {
  {
    WordDictionary wd;
    cmdAdd(wd, "bad");
    cmdAdd(wd, "dad");
    cmdAdd(wd, "mad");
    test(wd, "pad");
    test(wd, "bad");
    test(wd, ".ad");
    test(wd, "b..");
  }
  return 0;
}
