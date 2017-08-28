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
#include <limits>

#include "ConsistentHashPlanner.hh"
#include "UserStore.hh"

using namespace std;

void testDistribution(MachineId totalNumMachines = 10U) {
  ConsistentHashPlanner planner(numeric_limits<HashCode>::max(), 200U);

  MachineId id = 0U;
  for (; id < totalNumMachines; ++id) {
    planner.addMachine(id);
  }

  RandomHashCodeGenerator gen;
  auto counter = vector<int>(totalNumMachines, 0);
  auto repeat = 100000;
  for (auto i = 0; i < repeat; ++i) {
    auto hashcode = gen.generate();
    auto hitMachineId = planner.getMachineIdByHashCode(hashcode);
    counter[hitMachineId] += 1;
  }

  double stdev = 0.0, mean = static_cast<double>(repeat) / static_cast<double>(totalNumMachines);
  for (MachineId i = 0U; i < counter.size(); ++i) {
    cout << i << ": " << counter[i] << "\n";
    auto diff = static_cast<double>(counter[i]) - mean;
    stdev += diff * diff;
  }
  cout << "stdev: " << sqrt(stdev / static_cast<double>(repeat)) << "\n";
}

void testMigration(MachineId totalNumMachines = 10U) {
  ConsistentHashPlanner planner(numeric_limits<HashCode>::max(), 100U);

  MachineId id = 0U;
  for (; id < totalNumMachines; ++id) {
    planner.addMachine(id);
  }

  auto steps = planner.addMachine(id);
  for (const auto& step : steps) {
    cout << "dest: " << step.dest
         << " <- src: " << step.src
         << " totalLength: " << step.totalLength
         << "\n";
    for (const auto& range : step.ranges) {
      cout << "  [" << range.start
           << ", " << range.end << "]\n";
    }
  }
}

void testSaveAndLoad() {
  ConsistentHashPlanner planner(numeric_limits<HashCode>::max(), 200U);

  MachineId id = 0U, totalNumMachines = 100U;
  for (; id < totalNumMachines; ++id) {
    planner.addMachine(id);
  }

  RandomHashCodeGenerator gen;
  const string shardsConfFile = "./data/dist-db-1/shards.conf";
  planner.saveTo(shardsConfFile);

  ConsistentHashPlanner planner2(shardsConfFile);

  for (auto i = 0; i < 10; ++i) {
    auto hashcode = gen.generate();
    auto hit1 = planner.getMachineIdByHashCode(hashcode);
    auto hit2 = planner2.getMachineIdByHashCode(hashcode);
    cout << (hit1 == hit2) << "\t" << hashcode << "\t" << hit1 << "\t" << hit2 << "\n";
  }
}

void testUserStorePut() {
  UserStore client("./data/dist-db-1/db-002");

  for (auto i = 0U; i < 10; ++i) {
    auto userId = i;
    auto info = "I am user " + to_string(userId);
    client.put(userId, info);
  }
}

void testUserStoreGet(RowId userId) {
  UserStore client("./data/dist-db-1/db-002");
  auto res = client.get(userId);

  cout << "get(" << userId << "): ";
  if (res.empty()) {
    cout << "NULL\n";
  } else {
    cout << res[0].id << ", " << res[0].info << "\n";
  }
}

void testUserStoreRange(RowId start, RowId end) {
  UserStore client("./data/dist-db-1/db-002");
  auto res = client.range(start, end);

  cout << "range(" << start << ", " << end << "):";
  if (res.empty()) {
    cout << " NULL\n";
  } else {
    cout << "\n";
    for (const auto& record : res) {
      cout << "  " << record.id << ", " << record.info << "\n";
    }
  }
}

void testUserStoreClear() {
  UserStore client("./data/dist-db-1/db-002");
  client.clear();
}

int main(int argc, char* argv[]) {
  // testDistribution();
  // testMigration();
  // testSaveAndLoad();
  testUserStorePut();
  // testUserStoreGet(8173472720451418401);
  // testUserStoreGet(8173472720451418400);
  // testUserStoreRange(7903501305850404049, 8086459389438606843);
  // testUserStoreClear();
  return 0;
}
