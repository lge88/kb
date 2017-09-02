#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

vector<vector<int>> splitPages(const vector<int>& hosts, int pageSize) {
  vector<vector<int> > res;
  if (pageSize <= 0) return res;
  vector<int> remains = hosts;

  while (!remains.empty()) {
    unordered_set<int> hostSet;
    vector<int> page, next;
    for (const auto& host : remains) {
      // host is unique in this page and page is not filled up
      if (page.size() < pageSize && hostSet.find(host) == hostSet.end()) {
        hostSet.insert(host);
        page.push_back(host);
      } else {
        next.push_back(host);
      }
    }

    // While page is still not filled up, insert hosts one by one
    // regardless of uniqueness
    int i = 0, n = next.size();
    while (i < n && page.size() < pageSize) {
      page.push_back(next[i]);
      ++i;
    }

    // Update res
    res.push_back(page);

    // Update remains
    remains.clear();
    remains.insert(remains.begin(), next.begin() + i, next.end());
  }
  return res;
}

void printPage(const vector<int>& page, ostream& to) {
  for (int i = 0, n = page.size(); i < n; ++i) {
    to << (i > 0 ? "," : "") << page[i];
  }
}

void printRes(const vector<vector<int>>& res, ostream& to) {
  for (int i = 0, n = res.size(); i < n; ++i) {
    if (i > 0) to << " / ";
    printPage(res[i], to);
  }
}

void test(const vector<int>& hosts, int pageSize) {
  cout << "input: ";
  printPage(hosts, cout);
  cout << "\n";

  auto res = splitPages(hosts, pageSize);
  cout << "output: ";
  printRes(res, cout);
  cout << "\n\n";
}

int main(int argc, char* argv[]) {

  test({ 1,2,3,4,1,5,1,2,3,1,3 },
       5);

  test({ 1,1,1,1,1,1,2,3 },
       2);

  test({ 1,2,3,4,5,6,7,8,9 },
       3);

  test({ },
       3);

  test({ },
       0);

  test({ 1 },
       0);

  return 0;
}
