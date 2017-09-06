#include <algorithm>
#include <iostream>
#include <iterator>
#include <forward_list>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int getHostId(const string& record) {
  auto pos = record.find(',');
  if (pos == string::npos) {
    throw runtime_error("Bad record.");
  }
  return stoi(record.substr(0, pos));
}

vector <string> paginate(int num, vector <string> results) {
  vector<string> res;
  if (num <= 0) throw runtime_error("num is must be greater or equal to zero.");

  // Linked list node value is (index, hostId) pair
  using Node = pair<int, int>;
  forward_list<Node> remains = { { -1, -1 } };
  // First element is dummy node
  auto prev = begin(remains);
  for (int i = 0, n = results.size(); i < n; ++i) {
    prev = remains.emplace_after(prev, i, getHostId(results[i]));
  }

  while (next(begin(remains)) != end(remains)) {
    unordered_set<int> seen;
    int count = 0;

    prev = remains.begin();
    for (auto b = next(prev), e = end(remains); b != e && count < num;) {
      int index = b->first, hostId = b->second;
      // page is not filed and hostId is unique in current page
      if (seen.find(hostId) == seen.end()) {
        res.push_back(results[index]);
        seen.insert(hostId);
        count += 1;
        b = remains.erase_after(prev);
      } else {
        prev = b;
        b = next(b);
      }
    }

    // If page is still not filled up, insert record ignore unique hostid constraint
    prev = begin(remains);
    for (auto b = next(prev), e = end(remains); b != e && count < num; b = remains.erase_after(prev)) {
      res.push_back(results[b->first]);
      count += 1;
    }

    // There are more records, put a separator
    if (next(begin(remains)) != end(remains)) {
      res.push_back("");
    }
  }
  return res;
}


void printPage(const vector<int>& page, ostream& to) {
  for (int i = 0, n = page.size(); i < n; ++i) {
    to << (i > 0 ? "," : "") << page[i];
  }
}

void printRes(const vector<string>& res, ostream& to) {
  for (const auto& s : res) {
    to << s << "\n";
  }
}

void test(const vector<string>& records, int pageSize) {
  cout << "input:\n";
  printRes(records, cout);
  cout << "\n";

  auto res = paginate(pageSize, records);
  cout << "output:\n";
  printRes(res, cout);
  cout << "\n\n";
}

int main(int argc, char* argv[]) {
  vector<string> records = {
    "1,28,300.6,San Francisco",
    "4,5,209.1,San Francisco",
    "20,7,203.4,Oakland",
    "6,8,202.9,San Francisco",
    "6,10,199.8,San Francisco",
    "1,16,190.5,San Francisco",
    "6,29,185.3,San Francisco",
    "7,20,180.0,Oakland",
    "6,21,162.2,San Francisco",
    "2,18,161.7,San Jose",
    "2,30,149.8,San Jose",
    "3,76,146.7,San Francisco",
    "2,14,141.8,San Jose",
  };
  test(records, 5);

  records = {
    "1,28,100.3,Paris",
    "4,5,99.2,Paris",
    "2,7,90.5,Paris",
    "8,8,87.6,Paris",
    "6,10,85.6,Paris",
    "3,16,82.1,Paris",
    "7,29,81.1,Paris",
    "9,20,78.9,Paris",
    "12,21,74.3,Paris",
  };
  test(records, 3);
}
