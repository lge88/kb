#ifndef __CPP_COMM_HH
#define __CPP_COMM_HH

// A utility function to compares two sorted record list. Implement
// the functionality of GNU coreutils `comm' command.
template<
  typename RecordType,
  typename RecordIterType,
  typename RecordComparator,
  // void callback(const RecordType&, int group)
  // group == 1 => unique to first records source
  // group == 2 => unique to second records source
  // group == 3 => common
  typename RecordCallback
  >
void comm(const RecordIterType& aBeg, const RecordIterType& aEnd,
          const RecordIterType& bBeg, const RecordIterType& bEnd,
          const RecordComparator& comparator,
          const RecordCallback& callback) {
  RecordIterType aIt = aBeg, bIt = bBeg;
  while (aIt != aEnd && bIt != bEnd) {
    // a < b, *aIt is uniq to A
    if (comparator(*aIt, *bIt)) {
      callback(*aIt, 1);
      ++aIt;
      continue;
    }

    // b < a, *bIt is uniq to B
    if (comparator(*bIt, *aIt)) {
      callback(*bIt, 2);
      ++bIt;
      continue;
    }

    // a == b, common records
    callback(*aIt, 3);
    ++aIt;
    ++bIt;
  }

  while (aIt != aEnd) {
    callback(*aIt, 1);
    ++aIt;
  }

  while (bIt != bEnd) {
    callback(*bIt, 2);
    ++bIt;
  }
}

#endif // __CPP_COMM_HH
