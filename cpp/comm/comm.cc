#include <iostream>
#include <fstream>
#include <iterator>
#include <string>

#include "comm.hh"

namespace {

#define FLAG_SUPPRESS_COLUMN_1 0x01
#define FLAG_SUPPRESS_COLUMN_2 0x02
#define FLAG_SUPPRESS_COLUMN_3 0x04

struct Record {
  std::string line_;
};

std::istream& operator>>(std::istream& src, Record& record) {
  std::getline(src, record.line_);
}

typedef std::istream_iterator<Record> RecordIter;

struct Comparator {
  bool operator() (const Record& a, const Record& b) const {
    return a.line_ < b.line_;
  }
};

class Reporter {
 public:
  Reporter(std::ostream& dest, unsigned int flags = 0U, const std::string& delimiter = "\t")
      :
      dest_(dest),
      flags_(flags)
  {
    // 0 is dummy, since group can only be 1, 2, 3
    paddings_[0] = "";

    // default settings
    paddings_[1] = "";
    paddings_[2] = delimiter;
    paddings_[3] = delimiter + delimiter;

    // paddings_[2]
    if (flags_ & FLAG_SUPPRESS_COLUMN_1) {
      paddings_[2] = "";
    }

    // paddings_[3]
    int originalLen = paddings_[3].size(), suppressed = 0;
    if (flags_ & FLAG_SUPPRESS_COLUMN_1) {
      ++suppressed;
    }
    if (flags_ & FLAG_SUPPRESS_COLUMN_2) {
      ++suppressed;
    }
    paddings_[3].erase(originalLen - suppressed);
  }

  void operator() (const Record& record, int group) const {
    if (group == 1 && flags_ & FLAG_SUPPRESS_COLUMN_1) return;
    if (group == 2 && flags_ & FLAG_SUPPRESS_COLUMN_2) return;
    if (group == 3 && flags_ & FLAG_SUPPRESS_COLUMN_3) return;
    dest_ << paddings_[group] << record.line_ << '\n';
  }

 private:
  std::ostream& dest_;
  unsigned int flags_;
  std::string paddings_[4];
};

} // namespace

int main(int argc, char* argv[]) {
  // const char* file1 = argv[1];
  // const char* file2 = argv[2];
  const char* file1 = "data/f1.txt";
  const char* file2 = "data/f2.txt";

  std::ifstream ifs1(file1), ifs2(file2);
  RecordIter beg1(ifs1), end1 = RecordIter();
  RecordIter beg2(ifs2), end2 = RecordIter();

  Comparator comparator;

  unsigned int flags = 0U;
  // unsigned int flags = FLAG_SUPPRESS_COLUMN_3;
  // unsigned int flags = FLAG_SUPPRESS_COLUMN_1 | FLAG_SUPPRESS_COLUMN_2;
  const std::string& delimiter = "\t";
  Reporter reporter(std::cout, flags, delimiter);

  comm<Record, RecordIter, Comparator, Reporter>
      (beg1, end1, beg2, end2, comparator, reporter);
}
