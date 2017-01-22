#ifndef MAX_PRIORITY_QUEUE_HH
#define MAX_PRIORITY_QUEUE_HH

#include <unordered_map>
#include <utility>
// #include <stdexcept>

template <typename PriorityType = int,
          typename KeyType = int,
          typename ValType = int>
class MaxPriorityQueue {
 public:
  MaxPriorityQueue() {}

  void putWithPriority(const KeyType& key, const ValType& val, const PriorityType& priority) {
    if (contains(key)) {
      getMutable(key) = val;
      updatePriority(key, priority);
    } else {
      size_t index = heap_.size();
      data_[key] = std::make_pair(index, val);
      heap_.push_back(std::make_pair(key, priority));
      updatePriority(key, priority, true);
    }
  }

  bool contains(const KeyType& key) const {
    return data_.find(key) != data_.end();
  }

  size_t size() const {
    return heap_.size();
  }

  bool empty() const {
    return size() == 0;
  }

  const ValType& get(const KeyType& key) const {
    return data_.at(key).second;
  }

  ValType& getMutable(const KeyType& key) {
    return data_.at(key).second;
  }

  const KeyType& getMaxKey() const {
    if (size() == 0) {
      std::ostringstream oss;
      oss << "Tried to getMaxKey from empty queue";
      throw std::runtime_error(oss.str());
    }

    return heap_[0].first;
  }

  const ValType& getMax() const {
    return get(getMaxKey());
  }

  const ValType& extractMax() {
    const ValType& res = getMax();
    swap(heap_.back(), heap_.front());
    heap_.pop_back();
    sink(0);
    return res;
  }

  void updatePriority(const KeyType& key, const PriorityType& newPriority, bool force = false) {
    if (!contains(key)) {
      std::ostringstream oss;
      oss << "Can not found value by key: " << key;
      throw std::runtime_error(oss.str());
    }

    size_t index = data_[key].first;
    const PriorityType oldPriority = heap_[index].second;
    heap_[index].second = newPriority;

    // swim up
    if (force || newPriority > oldPriority) {
      swim(index);
    }
    // sink down
    else {
      sink(index);
    }
  }

 private:
  // KeyType => (indexInHeap, ValType)
  std::unordered_map<KeyType, std::pair<size_t, ValType> > data_;
  std::vector<std::pair<KeyType, PriorityType> > heap_;

  void swim(size_t index) {
    if (index == 0) return;
    size_t parent = (index - 1) >> 1;
    while (heap_[index].second > heap_[parent].second) {
      std::swap(heap_[index], heap_[parent]);
      if (parent == 0) break;
      index = parent;
      parent = (index - 1) >> 1;
    }
  }

  void sink(size_t index) {
    size_t left = 2 * index + 1;
    size_t largest = index;

    while (left < heap_.size()) {
      if (heap_[left].second > heap_[index].second) largest = left;

      size_t right = left + 1;
      if (right < heap_.size() && heap_[right].second > heap_[largest].second) largest = right;

      if (largest == index) break;
      swap(heap_[largest], heap_[index]);

      index = largest;
      left = 2 * index + 1;
    }
  }
};

#endif // MAX_PRIORITY_QUEUE_HH
