#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct Point {
  int x, y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
};

int gcd(int a, int b) {
  while (b %= a) swap(a, b);
  return a;
}

class Solution {
 public:
  struct Slop {
    int dx, dy;
    Slop(const Point& p1, const Point& p2): dx(p2.x - p1.x), dy(p2.y - p1.y) {
      if (dx == 0 && dy != 0) {
        dy = 1;
      } else if (dx != 0 && dy == 0) {
        dx = 1;
      } else if (dx != 0 && dy != 0) {
        if (dx < 0) {
          dx *= -1;
          dy *= -1;
        }
        int c = gcd(dx, abs(dy));
        dx /= c;
        dy /= c;
      }
    }
  };

  struct SlopCompare {
    bool operator() (const Slop& s1, const Slop& s2) const {
      return s1.dx == s2.dx ? s1.dy < s2.dy : s1.dx < s2.dx;
    }
  };

  int maxPoints(vector<Point>& points) {
    int n = points.size();
    int res = 0;
    for (int i = 0; i < n; ++i) {
      const Point& p1 = points[i];
      map<Slop, int, SlopCompare> countsBySlop;
      map<Slop, int, SlopCompare>::iterator it;
      int sameAsP1 = 1, maxCount = 0;
      for (int j = i + 1; j < n; ++j) {
        const Point& p2 = points[j];
        const Slop s(p1, p2);
        if (s.dx == 0 && s.dy == 0) {
          sameAsP1++;
          continue;
        }

        it = countsBySlop.find(s);
        if (it == countsBySlop.end()) {
          it = countsBySlop.insert(pair<Slop, int>(s, 1)).first;
        } else {
          it->second++;
        }
        maxCount = max(maxCount, it->second);
      }
      res = max(res, maxCount + sameAsP1);
    }
    return res;
  }
};

void test(vector<Point>& points) {
  Solution sol;
  cout << "points.size(): " << points.size() << "\n";
  cout << "maxPoints: " << sol.maxPoints(points) << "\n";
}

int main(int argc, char* argv[]) {
  {
    vector<Point> pts = { {0,0} };
    test(pts);
  }
  {
    vector<Point> pts = { {0,0}, {1,1} };
    test(pts);
  }
  {
    vector<Point> pts = { {0,0}, {1,1}, {0,0} };
    test(pts);
  }
  {
    vector<Point> pts = { {0,0}, {0,0}, {0,0} };
    test(pts);
  }
  {
    vector<Point> pts = {{0,9},{138,429},{115,359},{115,359},{-30,-102},{230,709},{-150,-686},{-135,-613},{-60,-248},{-161,-481},{207,639},{23,79},{-230,-691},{-115,-341},{92,289},{60,336},{-105,-467},{135,701},{-90,-394},{-184,-551},{150,774}};
    test(pts);
  }
  return 0;
}
