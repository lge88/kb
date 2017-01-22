#define CATCH_CONFIG_MAIN
#include "external/catch.hpp"

#include "MaxPriorityQueue.hh"
#include <random>

TEST_CASE( "MaxPriorityQueue", "[MaxPriorityQueue]" ) {
  MaxPriorityQueue<> q;
  q.putWithPriority(0, 0, 15);
  q.putWithPriority(1, 1, 8);
  q.putWithPriority(2, 2, 5);
  q.putWithPriority(3, 3, 1);
  q.putWithPriority(4, 4, 4);
  q.putWithPriority(5, 5, 2);

  SECTION("contains()") {
    REQUIRE(q.contains(0) == true);
    REQUIRE(q.contains(1) == true);
    REQUIRE(q.contains(2) == true);
    REQUIRE(q.contains(3) == true);
    REQUIRE(q.contains(4) == true);
    REQUIRE(q.contains(5) == true);
    REQUIRE(q.contains(6) == false);
  }

  SECTION("size() & empty()") {
    REQUIRE(q.size() == 6);
    REQUIRE(q.empty() == false);
  }

  SECTION("get()") {
    REQUIRE(q.get(0) == 0);
    REQUIRE(q.get(1) == 1);
    REQUIRE(q.get(2) == 2);
    REQUIRE(q.get(3) == 3);
    REQUIRE(q.get(4) == 4);
    REQUIRE(q.get(5) == 5);
    REQUIRE_THROWS(q.get(6));
  }

  SECTION("getMutable()") {
    REQUIRE(q.get(0) == 0);
    q.getMutable(0) = 20;
    REQUIRE(q.get(0) == 20);
    REQUIRE_THROWS(q.getMutable(6));
  }

  SECTION("getMaxKey() & getMax()") {
    REQUIRE(q.getMaxKey() == 0);
    REQUIRE(q.getMax() == 0);
  }

  SECTION("extractMax()") {
    REQUIRE(q.extractMax() == 0);
    REQUIRE(q.extractMax() == 1);
    REQUIRE(q.extractMax() == 2);
    REQUIRE(q.extractMax() == 4);
    REQUIRE(q.extractMax() == 5);
    REQUIRE(q.extractMax() == 3);
    REQUIRE_THROWS(q.extractMax());
    REQUIRE_THROWS(q.extractMax());
  }

  SECTION("putWithPriority()") {
    q.putWithPriority(20, 20, 14);
    REQUIRE(q.extractMax() == 0);
    REQUIRE(q.extractMax() == 20);
    REQUIRE(q.extractMax() == 1);
    REQUIRE(q.extractMax() == 2);
    REQUIRE(q.extractMax() == 4);
    REQUIRE(q.extractMax() == 5);
    REQUIRE(q.extractMax() == 3);
    REQUIRE_THROWS(q.extractMax());
    REQUIRE_THROWS(q.extractMax());
  }

  SECTION("updatePriority() - up") {
    q.updatePriority(3, 14);
    REQUIRE(q.extractMax() == 0);
    REQUIRE(q.extractMax() == 3);
    REQUIRE(q.extractMax() == 1);
    REQUIRE(q.extractMax() == 2);
    REQUIRE(q.extractMax() == 4);
    REQUIRE(q.extractMax() == 5);
    REQUIRE_THROWS(q.extractMax());
    REQUIRE_THROWS(q.extractMax());
  }
}

TEST_CASE( "Sort with MaxPriorityQueue", "[sort]" ) {
  SECTION("sort random array") {
    std::vector<int> A;
    for (int i = -500; i <= 500; ++i) A.push_back(i);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(A.begin(), A.end(), g);

    MaxPriorityQueue<> q;
    for (auto x : A) q.putWithPriority(x, x, x);

    std::vector<int> sorted;
    while (!q.empty()) sorted.push_back(q.extractMax());
    std::reverse(sorted.begin(), sorted.end());

    REQUIRE(sorted.size() == A.size());

    int expectedVal = -500;
    for (auto x : sorted) {
      REQUIRE(x == expectedVal);
      ++expectedVal;
    }
  }
}
