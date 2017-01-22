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

using namespace std;

class Solution {
 public:
  // Axis-Aligned-Bounding-Box
  struct AABB {
    int left_, right_, bottom_, top_;
    AABB(): left_(0), right_(0), bottom_(0), top_(0) {}
    void setFromABCD(int A, int B, int C, int D) {
      left_ = min(A, C);
      right_ = max(A, C);
      bottom_ = min(B, D);
      top_ = max(B, D);
    }
    int getArea() const {
      return (right_ - left_) * (top_ - bottom_);
    }
  };

  int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    // 1) Construct bounding box b1, b2 from given points
    AABB b1, b2;
    b1.setFromABCD(A, B, C, D);
    b2.setFromABCD(E, F, G, H);

    if (b1.left_ > b2.left_) swap(b1, b2);
    // Now b1.left_ <= b2.left_

    int aTotal = b1.getArea() + b2.getArea();
    int aIntersection = 0;

    if (b2.bottom_ >= b1.top_ || b2.left_ >= b1.right_) {
      // No overlap 1), 2), 4), 6)
      aIntersection = 0;
    } else if (b2.bottom_ > b1.bottom_) {
      // 3)
      int w = min(b1.right_, b2.right_) - b2.left_;
      int h = min(b1.top_, b2.top_) - b2.bottom_;
      aIntersection = w * h;
    } else {
      // 5)
      int w = min(b1.right_, b2.right_) - b2.left_;
      int h = max(0, min(b1.top_, b2.top_) - b1.bottom_);
      aIntersection = w * h;
    }

    return aTotal - aIntersection;
  }
};

void test(int A, int B, int C, int D, int E, int F, int G, int H) {
  Solution sol;
  cout << "A: " << A << " B: " << B << " C: " << C << " D: " << D << "\n";
  cout << "E: " << E << " F: " << F << " G: " << G << " H: " << H << "\n";
  cout << "area: " << sol.computeArea(A, B, C, D, E, F, G, H) << "\n";
}

int main(int argc, char* argv[]) {
  {
    test(-3, 0, 3, 4, 0, -1, 9, 2);
  }
  {
    test(0, -1, 9, 2, -3, 0, 3, 4);
  }
  return 0;
}
