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
  struct Item { int freq, key, val; };
  using RecencyList = list<Item>;
  using FrequencyList = list<RecencyList>;

  // A list of itemLists, head is most frequent
  // A 2D list, first dimension ordered from most frequent to least frequent
  // second dimension ordered from most recent to least recent
  FrequencyList freqList;
  unordered_map<int, RecencyList::iterator> keyTable;
  unordered_map<int, FrequencyList::iterator> freqTable;
  int cap, size;

  using KeyIter = unordered_map<int, RecencyList::iterator>::iterator;
  void touch(KeyIter it) {
    // recIter is the iterator which we want to remove
    auto recIter = it->second;
    // Get the values of item before it gets invalidate
    auto item = *recIter;
    auto key = item.key;
    auto val = item.val;
    auto freq = item.freq;
    auto newFreq = freq + 1;

    // 1) Add a new item { newFreq, key, val } to cache
    // 2) Remove old item { freq, key, val } from cache

    // Do we need to insert a new RecencyList for the new frequency?
    auto freqIter = freqTable[freq];
    if (freqIter == begin(freqList) || prev(freqIter)->begin()->freq != newFreq) {
      // insert an empty RecencyList to the front
      // Add a new entry in freqTable
      freqTable[newFreq] = freqList.insert(freqIter, RecencyList());
    }
    freqTable[newFreq]->push_front({ newFreq, key, val });
    it->second = freqTable[newFreq]->begin();

    // Remove old item from container
    freqIter->erase(recIter);
    // if freqIter is empty, remove from freqList and freqTable
    if (freqIter->empty()) {
      freqList.erase(freqIter);
      freqTable.erase(freq);
    }
  }

 public:
  LFUCache(int capacity): cap(capacity), size(0) {}

  int get(int key) {
    auto it = keyTable.find(key);
    if (it == keyTable.end()) return -1;
    touch(it);
    return it->second->val;
  }

  void put(int key, int value) {
    auto it = keyTable.find(key);
    if (it != keyTable.end()) {
      it->second->val = value;
      touch(it);
      return;
    }

    // Add a new key
    // if new size will exceed capacity, invalidate least frequent element first
    if (size + 1 > cap && size > 0) {
      auto itemToRemove = freqList.back().back();
      auto containerIter = freqTable[itemToRemove.freq];
      auto it = keyTable[itemToRemove.key];
      keyTable.erase(itemToRemove.key);
      containerIter->erase(it);
      if (containerIter->empty()) {
        freqList.erase(containerIter);
        freqTable.erase(itemToRemove.freq);
      }
      size -= 1;
    }

    if (size >= cap) return;

    Item item = { 1, key, value };
    if (freqTable.find(item.freq) == freqTable.end()) {
      freqTable[item.freq] = freqList.insert(freqList.end(), RecencyList());
    }
    freqTable[item.freq]->push_front(item);
    keyTable[item.key] = freqTable[item.freq]->begin();
    size += 1;
  }

  void showState(ostream& to) {
    to << "\ncache state\n";
    to << "cap: " << cap << ", size: " << size << "\n";
    to << "freqList:\n";
    int i = 0;
    for (auto x : freqList) {
      int j = 0;
      cout << (i++) << " :";
      for (auto y : x) {
        to << " (j:" << (j++) << ", k:" << y.key << ", v:" << y.val << ", f:" << y.freq << ")";
      }
      to << "\n";
    }
    to << "freqTable:\n";
    for (auto p : freqTable) {
      to << p.first << " => " << distance(begin(freqList), p.second) << "\n";
    }
    to << "keyTable:\n";
    for (auto p : keyTable) {
      to << p.first << " => " << distance(begin(*freqTable[p.second->freq]), p.second) << "\n";
    }
    cout << "\n";
  }
};

void doGet(LFUCache& cache, int key) {
  cerr << "get(" << key << ") => " << cache.get(key) << "\n";
  cache.showState(cerr);
}

void doPut(LFUCache& cache, int key, int val) {
  cerr << "put(" << key << ", " << val << ")\n";
  cache.put(key, val);
  cache.showState(cerr);
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

int main(int argc, char* argv[]) {
  test2();
  return 0;
}
