#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Trie {
 public:
  Trie() {
    root_.reset(new TrieNode);
  }

  void insert(string word) {
    TrieNode* p = root_.get();
    for (auto c : word) {
      int j = c - 'a';
      if (p->children_[j].get() == nullptr) {
        p->children_[j].reset(new TrieNode);
      }
      p = p->children_[j].get();
    }
    p->valid_ = true;
  }

  bool search(string word) {
    TrieNode* node = searchInternal(word);
    return node && node->valid_;
  }

  bool startsWith(string prefix) {
    return searchInternal(prefix) != nullptr;
  }

 private:
  struct TrieNode {
    bool valid_ = false;
    unique_ptr<TrieNode> children_[26];
  };

  unique_ptr<TrieNode> root_;

  TrieNode* searchInternal(const string& word) const {
    TrieNode* p = root_.get();
    for (char c : word) {
      int j = c - 'a';
      if (p->children_[j].get() == nullptr) {
        return nullptr;
      }
      p = p->children_[j].get();
    }
    return p;
  }
};

int main(int argc, char* argv[]) {
  vector<string> words = { "abc", "aa", "abcde", "xxx", "abef" };

  Trie t;
  for (auto word : words) t.insert(word);

  cout << "search(abc): " << t.search("abc") << "\n";
  cout << "search(ab): " << t.search("ab") << "\n";
  cout << "startWith(ab): " << t.startsWith("ab") << "\n";
  cout << "startWith(xx): " << t.startsWith("xx") << "\n";
  cout << "startWith(xxx): " << t.startsWith("xxx") << "\n";
  cout << "startWith(xxxx): " << t.startsWith("xxxx") << "\n";
  cout << "search(aa): " << t.search("aa") << "\n";
  cout << "search(abcde): " << t.search("abcde") << "\n";
  cout << "search(abef): " << t.search("abef") << "\n";
  cout << "search(abe): " << t.search("abe") << "\n";
  cout << "startsWith(abe): " << t.startsWith("abe") << "\n";
}
