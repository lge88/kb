#include <vector>
#include <mutex>

using std::vector;
using std::mutex;
using std::lock_guard;

class Logger {
 public:
  Logger();
  uint64_t append(int val);
  int read(uint64_t seqId) const;
  void truncate(uint64_t seqId);

 private:
  vector<int> data_;
  uint64_t seqIdStart_;
  mutable mutex mtx_;
};

Logger::Logger(): seqIdStart_(0U) {}

uint64_t Logger::append(int val) {
  lock_guard<mutex> lock(mtx_);
  data_.push_back(val);
  return data_.size() - 1;
}

int Logger::read(uint64_t seqId) const {
  lock_guard<mutex> lock(mtx_);
  uint64_t i = seqId - seqIdStart_;
  return i < data_.size() ? data_[i] : -1;
}

void Logger::truncate(uint64_t seqId) {
  lock_guard<mutex> lock(mtx_);
  if (seqId < seqIdStart_) return;
  uint64_t newDataStart = seqId - seqIdStart_ + 1;
  if (newDataStart >= data_.size()) {
    data_.clear();
  } else {
    vector<int> newData(data_.begin() + newDataStart, data_.end());
    data_.swap(newData);
  }
  seqIdStart_ = seqId + 1;
}
