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

class LRUCache{
 public:
  LRUCache(int capacity):
      capacity_(capacity),
      size_(0),
      head_(NULL),
      tail_(NULL)
  {}

  ~LRUCache() {
    Node* p = head_;
    while (p != NULL) {
      Node* next = p->next_;
      delete p;
      p = next;
    }
  }

  int get(int key) {
    unordered_map<int, Node*>::const_iterator it = data_.find(key);
    if (it == data_.end()) return -1;

    Node* node = it->second;
    makeHead(node);
    return node->val_;
  }

  void set(int key, int value) {
    unordered_map<int, Node*>::const_iterator it = data_.find(key);
    if (it != data_.end()) {
      Node* node = it->second;
      node->val_ = value;
      makeHead(node);
      return;
    }

    // not found, insert to cache
    Node* node = new Node(key, value);
    data_[key] = node;
    if (head_ == NULL) {
      head_ = node;
      tail_ = node;
    } else {
      node->next_ = head_;
      head_->prev_ = node;
      head_ = node;
    }

    ++size_;
    if (size_ > capacity_) {
      Node* newTail = tail_->prev_;
      newTail->next_ = NULL;
      data_.erase(tail_->key_);
      delete tail_;
      tail_ = newTail;
      --size_;
    }
  }

  void printDebugState(ostream& to) {
    to << "data_: [";
    for (unordered_map<int, Node*>::const_iterator it = data_.begin();
         it != data_.end(); ++it) {
      to << " " << it->first << "=>" << it->second->val_;
    }
    to << " ]\n";
    to << "queue: ";
    Node* p = head_;
    while (p != NULL) {
      to << "(" << p->key_ << "," << p->val_ << ") -> ";
      p = p->next_;
    }
    to << "NULL\n";
  }

 private:
  int capacity_;
  int size_;
  struct Node {
    int key_, val_;
    Node* prev_;
    Node* next_;
    Node(int k, int v): key_(k), val_(v), prev_(NULL), next_(NULL) {}
  };
  Node* head_;
  Node* tail_;
  unordered_map<int, Node*> data_;

  // Put node in the front of the queue. pre: node is not NULL
  void makeHead(Node* node) {
    if (node != head_) {
      Node* prev = node->prev_;
      Node* next = node->next_;
      prev->next_ = next;
      if (next != NULL) next->prev_ = prev;
      node->prev_ = NULL;
      node->next_ = head_;
      head_->prev_ = node;
      head_ = node;
      if (node == tail_) tail_ = prev;
    }
  }
};

void doGet(LRUCache& lru, int key) {
  cout << "get(" << key << "): " << lru.get(key) << "\n";
  lru.printDebugState(cout);
  cout << "\n";
}

void doSet(LRUCache& lru, int key, int val) {
  cout << "set(" << key << ", " << val << ")\n";
  lru.set(key, val);
  lru.printDebugState(cout);
  cout << "\n";
}

int main(int argc, char* argv[]) {
  {
    LRUCache lru(2);
    doSet(lru, 2, 1);
    doSet(lru, 1, 1);
    doGet(lru, 2);
    doSet(lru, 4, 1);
    doGet(lru, 1);
    doGet(lru, 2);
  }
  return 0;
}
