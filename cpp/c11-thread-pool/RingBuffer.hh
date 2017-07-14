#ifndef RING_BUFFER_HH
#define RING_BUFFER_HH

// Simple fixed size ring buffer, not thread safe.
template<typename T>
class RingBuffer {
 public:
  RingBuffer(size_t capacity);
  ~RingBuffer();
  bool enqueue(const T& item);
  bool dequeue(T& item);
  size_t size() const;
  bool full() const;
  bool empty() const;

 private:
  T* data_;
  size_t head_, len_, capacity_;

}; // class RingBuffer

template<typename T>
RingBuffer<T>::RingBuffer(size_t capacity)
    : capacity_(capacity),
      head_(0),
      len_(0) {
  data_ = new T[capacity_];
}

template<typename T>
RingBuffer<T>::~RingBuffer() {
  delete[] data_;
}

template<typename T>
bool RingBuffer<T>::enqueue(const T& item) {
  if (len_ == capacity_) return false;
  data_[(head_ + len_) % capacity_] = item;
  len_ += 1;
  return true;
}

template<typename T>
bool RingBuffer<T>::dequeue(T& item) {
  if (len_ == 0) return false;
  item = data_[head_];
  head_ = (head_ + 1) % capacity_;
  len_ -= 1;
  return true;
}

template<typename T>
size_t RingBuffer<T>::size() const {
  return len_;
}

template<typename T>
bool RingBuffer<T>::full() const {
  return len_ == capacity_;
}

template<typename T>
bool RingBuffer<T>::empty() const {
  return len_ == 0;
}

#endif // RING_BUFFER_HH
