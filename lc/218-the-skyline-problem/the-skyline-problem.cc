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
  struct CriticalPoint {
    int rectIndex_;
    enum Type { LEFT = 0, RIGHT };
    Type type_;
    int x_, y_;
  };

  struct ByX {
    bool operator()(const CriticalPoint& p1, const CriticalPoint& p2) const {
      if (p1.x_ == p2.x_) return p1.rectIndex_ < p2.rectIndex_;
      return p1.x_ < p2.x_;
    }
  };

  struct Rect {
    int i_;
    Rect(int i, const vector<vector<int> >& buildings):
        i_(i),
        buildings_(buildings)
    {}
    int getHeight() const {
      return buildings_[i_][2];
    }
   private:
    const vector<vector<int> >& buildings_;
  };

  struct ByBuildingHeight {
    bool operator()(const Rect& r1, const Rect& r2) const {
      // This is important! Otherwise building with same height will
      // never be insert to the set.
      if (r1.getHeight() == r2.getHeight()) return r1.i_ < r2.i_;
      return r1.getHeight() > r2.getHeight();
    }
  };

  vector<pair<int, int> > getSkyline(vector<vector<int> >& buildings) {
    vector<CriticalPoint> criticalPoints;
    vector<pair<int, int> > result;
    size_t n = buildings.size();
    if (n == 0) return result;

    for (size_t i = 0; i < n; ++i) {
      const int& h = buildings[i][2];
      CriticalPoint p1;
      p1.type_ = CriticalPoint::LEFT;
      p1.rectIndex_ = i;
      p1.x_ = buildings[i][0];
      p1.y_ = h;

      CriticalPoint p2;
      p2.type_ = CriticalPoint::RIGHT;
      p2.rectIndex_ = i;
      p2.x_ = buildings[i][1];
      p2.y_ = h;

      criticalPoints.push_back(p1);
      criticalPoints.push_back(p2);
    }
    sort(criticalPoints.begin(), criticalPoints.end(), ByX());

    set<Rect, ByBuildingHeight> activeRects;
    size_t nPoints = criticalPoints.size();
    for (size_t i = 0; i < nPoints; ++i) {
      CriticalPoint& p = criticalPoints[i];
      if (p.type_ == CriticalPoint::LEFT) {
        activeRects.insert(Rect(p.rectIndex_, buildings));
      } else {
        activeRects.erase(Rect(p.rectIndex_, buildings));
      }
      cout << "\n" << i << ": active: [ ";
      for (auto r : activeRects) cout << r.i_ << " ";
      cout << "] ";
      cout << "x_: " << p.x_ << " y_: " << p.y_ << "\n";

      if (activeRects.empty()) {
        p.y_ = 0;
      } else {
        p.y_ = activeRects.begin()->getHeight();
      }
      cout << "after: x_: " << p.x_ << " y_: " << p.y_ << "\n";
    }

    int prevHeight = -1;
    for (size_t i = 0; i < nPoints; ++i) {
      int x = criticalPoints[i].x_;
      // Only pick the height of last critical point with this same x
      int h = criticalPoints[i].y_;
      for (size_t j = i + 1; j < nPoints && criticalPoints[j].x_ == x; ++j) {
        h = criticalPoints[j].y_;
      }

      // Skip the ones without height difference
      // Would never happened in first run since prevHeight < 0 and h > 0
      if (h == prevHeight) continue;

      result.push_back(make_pair(x, h));
      prevHeight = h;
    }

    return result;
  }
};

void test(vector<vector<int> >& buildings) {
  Solution sol;
  cout << "buildings: [ ";
  for (auto b : buildings) {
    cout << "[ ";
    for (auto x : b) cout << x << " ";
    cout << "] ";
  }
  cout << "]\n";

  vector<pair<int, int> > skyline = sol.getSkyline(buildings);
  cout << "skyline: [ ";
  for (auto p : skyline) cout << "[" << p.first << ", " << p.second << "] ";
  cout << "]\n";
}

int main(int argc, char* argv[]) {
  {
    vector<vector<int> > buildings = {
      { 2, 9, 10 },
      { 3, 7, 15 },
      { 5, 12, 12 },
      { 15, 20, 10 },
      { 19, 24, 8 }
    };
    test(buildings);
  }
  {
    vector<vector<int> > buildings = {
      { 0, 2, 3 },
      { 2, 5, 3 }
    };
    test(buildings);
  }
  {
    vector<vector<int> > buildings = {
      { 0, 3, 3 },
      { 1, 5, 3 },
      { 2, 4, 3 },
      { 3, 7, 3 }
    };
    test(buildings);
  }

  return 0;
}
