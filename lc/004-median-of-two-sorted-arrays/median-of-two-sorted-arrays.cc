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
#include <cassert>

using namespace std;

class Solution {
 public:
  struct Slice {
    Slice(const vector<int>& arr)
        : arr_(arr) { reset(); }
    inline int kth(int k) const {
      if (k - 1 >= len_) throw runtime_error("Index out of bound.");
      int index = start_ + k - 1;
      return arr_[index];
    }
    inline void reset() {
      start_ = 0;
      len_ = arr_.size();
    }
    int start_, len_;

   private:
    const vector<int>& arr_;
  };

  double findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2) {
    int n = nums1.size() + nums2.size();
    Slice A(nums1), B(nums2);
    if (n % 2 == 0) {
      int a = findKth(A, B, n / 2);
      A.reset();
      B.reset();
      int b = findKth(A, B, n / 2 + 1);
      return 0.5 * (a + b);
    } else {
      return findKth(A, B, n / 2 + 1);
    }
  }

  int findKth(Slice& A, Slice& B, int k) {
    int m = A.len_, n = B.len_;
    if (m <= 0) return B.kth(k);
    if (n <= 0) return A.kth(k);
    if (k == 1) return min(A.kth(1), B.kth(1));

    int k1 = min(k / 2, m), k2 = k - k1;
    if (k2 > n) {
      k2 = n;
      k1 = k - k2;
    }
    int Ak1 = A.kth(k1), Bk2 = B.kth(k2);
    if (Ak1 == Bk2) return Ak1;
    if (Ak1 < Bk2) {
      A.start_ += k1;
      A.len_ -= k1;
      return findKth(A, B, k - k1);
    }
    B.start_ += k2;
    B.len_ -= k2;
    return findKth(A, B, k - k2);
  }
};

void test(const vector<int>& A, const vector<int>& B, double expected) {
  Solution sol;
  cout << "A: [ ";
  for (size_t i = 0; i < A.size(); ++i) cout << (i > 0 ? ", " : "") << A[i];
  cout << " ]\n";
  cout << "B: [ ";
  for (size_t i = 0; i < B.size(); ++i) cout << (i > 0 ? ", " : "") << B[i];
  cout << " ]\n";
  double actual = sol.findMedianSortedArrays(A, B);
  cout << "findMedianSortedArrays(A, B): " << actual << ", expected: " << expected << "\n\n";
  assert(fabs(actual - expected) < 1e-8);
}

int main(int argc, char* argv[]) {
  {
    vector<int> A = { 2, 3, 4 };
    vector<int> B = { 1 };
    test(A, B, 2.5);
  }
  {
    test({ 4 }, { 1, 2, 3 }, 2.5);
  }
  return 0;
}
