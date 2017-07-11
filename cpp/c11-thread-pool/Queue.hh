#ifndef QUEUE_HH
#define QUEUE_HH

#include <queue>
#include <mutex>

template<typename T>
class Queue {
 public:
  Queue(size_t capacity);
  bool enqueue(const T& item);
  bool dequeue(T& item);

 private:
  size_t capacity_;
  std::mutex mtx_;
  std::queue<T> data_;

}; // class Queue

template<typename T>
Queue<T>::Queue(size_t capacity)
    : capacity_(capacity) {}

template<typename T>
bool Queue<T>::enqueue(const T& item) {
  std::lock_guard<std::mutex> lock(mtx_);
  if (data_.size() >= capacity_) return false;
  data_.push(item);
  return true;
}

template<typename T>
bool Queue<T>::dequeue(T& item) {
  std::lock_guard<std::mutex> lock(mtx_);
  if (data_.empty()) return false;
  item = data_.front();
  data_.pop();
  return true;
}

#endif // QUEUE_HH
