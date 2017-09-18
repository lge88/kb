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
#include <list>

using namespace std;

class LFUCache {
  struct Item { int key, val, freq; };
  using RecencyList = list<Item>;
  using FrequencyList = list<RecencyList>;
  using ItemIter = RecencyList::iterator;
  using ContainerIter = FrequencyList::iterator;

  int cap;
  FrequencyList lst;
  unordered_map<int, pair<ContainerIter, ItemIter>> table;
  using TableIter = decltype(table)::iterator;

  void touch(TableIter tIter) {
    auto containerIter = tIter->second.first;
    auto itemIter = tIter->second.second;
    // 1) Add a new item with new freqency
    // 2) Remove old item
    auto newFreq = itemIter->freq + 1;
    Item newItem = { itemIter->key, itemIter->val, newFreq };
    auto newContainerIter = lst.end();
    // Insert a new RecencyList if there isn't one for newFreq
    if (containerIter == lst.begin() || prev(containerIter)->begin()->freq != newFreq) {
      newContainerIter = lst.insert(containerIter, RecencyList());
    } else {
      newContainerIter = prev(containerIter);
    }
    auto newItemIter = newContainerIter->insert(newContainerIter->begin(), newItem);
    // Update the entry in table associated with the key
    tIter->second = { newContainerIter, newItemIter };

    containerIter->erase(itemIter);
    if (containerIter->empty()) {
      lst.erase(containerIter);
    }
  }

 public:
  LFUCache(int capacity): cap(capacity) {}

  int get(int key) {
    auto tIter = table.find(key);
    if (tIter == table.end()) return -1;
    touch(tIter);
    return tIter->second.second->val;
  }

  void put(int key, int value) {
    if (cap <= 0) return;

    auto tIter = table.find(key);
    if (tIter != table.end()) {
      tIter->second.second->val = value;
      touch(tIter);
      return;
    }
    // Add a new key
    if (table.size() >= cap) {
      // invalidate the least frequent (least recent) key
      auto keyToRemove = lst.back().back().key;
      lst.back().pop_back();
      if (lst.back().empty()) {
        lst.pop_back();
      }
      table.erase(keyToRemove);
    }

    Item item = { key, value, 1 };
    auto containerIter = lst.end();
    if (lst.empty() || lst.back().front().freq != item.freq) {
      containerIter = lst.insert(lst.end(), RecencyList());
    } else {
      containerIter = prev(lst.end());
    }
    auto itemIter = containerIter->insert(containerIter->begin(), item);
    table[key] = { containerIter, itemIter };
  }

  void showState(ostream& to) {
    to << "\ncache state\n";
    to << "cap: " << cap << ", size: " << table.size() << "\n";
    to << "lst:\n";
    int i = 0;
    for (auto x : lst) {
      int j = 0;
      cout << (i++) << " :";
      for (auto y : x) {
        to << " (j:" << (j++) << ", k:" << y.key << ", v:" << y.val << ", f:" << y.freq << ")";
      }
      to << "\n";
    }
    to << "table:\n";
    for (auto p : table) {
      to << p.first << " => "
         << "(" << distance(begin(lst), p.second.first)
         << ", " << distance(begin(*p.second.first), p.second.second) << ")\n";
    }
    cout << "\n";
  }
};

void doGet(LFUCache& cache, int key) {
  cerr << "get(" << key << ") => " << cache.get(key) << "\n";
  // cache.showState(cerr);
}

void doPut(LFUCache& cache, int key, int val) {
  cerr << "put(" << key << ", " << val << ")\n";
  cache.put(key, val);
  // cache.showState(cerr);
}

void test1() {
  LFUCache cache(2);
  doPut(cache, 1, 1);
  doPut(cache, 2, 2);
  doGet(cache, 1);
  doPut(cache, 3, 3);
  doGet(cache, 2);
  doGet(cache, 3);
  doPut(cache, 4, 4);
  doGet(cache, 1);
  doGet(cache, 3);
  doGet(cache, 4);
}

void test2() {
  LFUCache cache(0);
  doPut(cache, 0, 0);
  doGet(cache, 0);
}

void test3() {
  LFUCache cache(10);
  doPut(cache,10,13);
  doPut(cache,3,17);
  doPut(cache,6,11);
  doPut(cache,10,5);
  doPut(cache,9,10);
  doGet(cache,13);
  doPut(cache,2,19);
  doGet(cache,2);
  doGet(cache,3);

  doPut(cache,5,25);
  doGet(cache,8);
  doPut(cache,9,22);
  doPut(cache,5,5);
  doPut(cache,1,30);
  doGet(cache,11);
  doPut(cache,9,12);
  doGet(cache,7);
  doGet(cache,5);
  doGet(cache,8);
  doGet(cache,9);

  doPut(cache,4,30);
  doPut(cache,9,3);
  doGet(cache,9);
  doGet(cache,10);
  doGet(cache,10);
  doPut(cache,6,14);
  doPut(cache,3,1);
  doGet(cache,3);
  doPut(cache,10,11);
  doGet(cache,8);
  doPut(cache,2,14);

  doGet(cache,1);
  doGet(cache,5);
  doGet(cache,4);
  doPut(cache,11,4);
  doPut(cache,12,24);
  doPut(cache,5,18);
  doGet(cache,13);
  doPut(cache,7,23);
  doGet(cache,8);
  doGet(cache,12);
  doPut(cache,3,27);
  doPut(cache,2,12);
  doGet(cache,5);
  doPut(cache,2,9);
  doPut(cache,13,4);
  doPut(cache,8,18);
  doPut(cache,1,7);
  doGet(cache,6);
  doPut(cache,9,29);
  doPut(cache,8,21);
  doGet(cache,5);
  doPut(cache,6,30);
  doPut(cache,1,12);
  doGet(cache,10);
  doPut(cache,4,15);
  doPut(cache,7,22);
  doPut(cache,11,26);
  doPut(cache,8,17);
  doPut(cache,9,29);
  doGet(cache,5);
  doPut(cache,3,4);
  doPut(cache,11,30);
  doGet(cache,12);

  doPut(cache,4,29);
  cache.showState(cerr);

  doGet(cache,3);
  doGet(cache,9);
  doGet(cache,6);
  doPut(cache,3,4);
  doGet(cache,1);
  doGet(cache,10);
  doPut(cache,3,29);
  doPut(cache,10,28);
  doPut(cache,1,20);
  doPut(cache,11,13);
  doGet(cache,3);
  doPut(cache,3,12);
  doPut(cache,3,8);
  doPut(cache,10,9);
  doPut(cache,3,26);
  doGet(cache,8);
  doGet(cache,7);
  doGet(cache,5);
  doPut(cache,13,17);
  doPut(cache,2,27);
  doPut(cache,11,15);
  doGet(cache,12);
  doPut(cache,9,19);
  doPut(cache,2,15);
  doPut(cache,3,16);
  doGet(cache,1);
  doPut(cache,12,17);
  doPut(cache,9,1);
  doPut(cache,6,19);
  doGet(cache,4);
  doGet(cache,5);
  doGet(cache,5);
  doPut(cache,8,1);
  doPut(cache,11,7);
  doPut(cache,5,2);
  doPut(cache,9,28);
  doGet(cache,1);
  doPut(cache,2,2);
  doPut(cache,7,4);
  doPut(cache,4,22);
  doPut(cache,7,24);
  doPut(cache,9,26);
  doPut(cache,13,28);
  doPut(cache,11,26);

  cache.showState(cerr);
}

int main(int argc, char* argv[]) {
  // test1();
  // test2();
  test3();
  return 0;
}
