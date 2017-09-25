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
#include <bitset>

using namespace std;

uint32_t parseIp(string ip) {
  uint32_t res = 0;
  istringstream iss(ip);
  string word;
  getline(iss, word, '.');
  res |= (stoi(word) << 24);

  getline(iss, word, '.');
  res |= (stoi(word) << 16);

  getline(iss, word, '.');
  res |= (stoi(word) << 8);

  getline(iss, word);
  res |= stoi(word);

  return res;
}

string stringifyIp(uint32_t ip) {
  ostringstream oss;
  uint32_t mask = (1 << 8) - 1;
  oss << ((ip >> 24) & mask) << "."
      << ((ip >> 16) & mask) << "."
      << ((ip >> 8) & mask) << "."
      << (ip & mask);
  return oss.str();
}

// numBits > 1
pair<uint32_t, uint32_t> cidrRange(uint32_t ip, int numBits) {
  int unused = 32 - numBits;
  // numBits = 4, unused = 28, mask: 0000 . '1' * 28
  // numBits = 1, unused = 31, mask: 0 . '1' * 31
  // numBits = 32, unused = 0, mask: '0' * 32
  uint32_t mask = (1 << unused) - 1;
  // cout << "numBits: " << numBits << ", mask: " << bitset<32>(mask) << "\n";

  uint32_t from = ip & (~mask);
  uint32_t to = ip | mask;
  return { from, to };
}

vector<string> ip2cidr(string startIp, string endIp) {
  auto from = parseIp(startIp), to = parseIp(endIp);
  // cout << "from: " << bitset<32>(from) << "\n";
  // cout << "to: " << bitset<32>(to) << "\n";
  // cout << "from: " << stringifyIp(from) << "\n";
  // cout << "to: " << stringifyIp(to) << "\n";
  vector<string> res;

  while (from <= to) {
    int numBits = 32;
    while (numBits - 1 > 0 && cidrRange(from, numBits - 1).first == from) {
      numBits = numBits - 1;
    }

    while (cidrRange(from, numBits).second > to) {
      numBits = numBits + 1;
    }

    int offset = 32 - numBits;
    uint32_t ip = from >> offset << offset;
    res.push_back(stringifyIp(ip) + "/" + to_string(numBits));

    from = cidrRange(from, numBits).second + 1;
  }

  return res;
}

void test(string startIp, string endIp) {
  cout << "From: " << startIp << "\n";
  cout << "To: " << endIp << "\n";
  auto res = ip2cidr(startIp, endIp);
  cout << "res:\n";
  for (auto x : res) cout << x << "\n";
  cout << "\n";
}

int main(int argc, char* argv[]) {

  test("5.10.64.127", "5.10.127.254");

  return 0;
}
