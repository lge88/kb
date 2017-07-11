#ifndef QUEUE_HH
#define QUEUE_HH

#include <deque>

template<typename T>
class Queue {
 public:
  void enqueue(const T& item);
  T dequeue();
  int size() const;
 private:
  std::deque<T> data_;
}; // class Queue

template<typename T>
void Queue<T>::enqueue(const T& item) {
  data_.push_back(item);
}

template<typename T>
T Queue<T>::dequeue() {
  T item = data_.front();
  data_.pop_front();
  return item;
}

template<typename T>
int Queue<T>::size() const {
  return data_.size();
}

#endif // QUEUE_HH
