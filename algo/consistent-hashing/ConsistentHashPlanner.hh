#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using HashCode = int64_t;
using MachineId = uint32_t;

struct HashCodeRange {
  HashCode start, end;
};

struct DataMigrationStep {
  MachineId src, dest;
  std::vector<HashCodeRange> ranges;
  HashCode totalLength;
};

class RandomHashCodeGenerator {
  std::random_device rd_;
  std::mt19937_64 gen_;
  std::uniform_int_distribution<HashCode> dis_;

 public:
  RandomHashCodeGenerator(HashCode seed) : rd_(), gen_(rd_()) {
    gen_.seed(seed);
  }
  RandomHashCodeGenerator() : rd_(), gen_(rd_()) {}
  HashCode generate() { return dis_(gen_); }
};

class ConsistentHashPlanner {
  HashCode n_, k_;

  RandomHashCodeGenerator randomGen_;

  // map from position on the hash ring to machineId
  std::map<HashCode, MachineId> machines_;

 public:
  ConsistentHashPlanner(HashCode n, HashCode k): n_(n), k_(k), randomGen_() {}

  ConsistentHashPlanner(const std::string& filename): n_(0U), k_(0U), randomGen_() {
    loadFrom(filename);
  }

  void loadFrom(const std::string& filename) {
    std::ifstream ifs(filename);
    deserializeFrom(ifs);
  }

  void saveTo(const std::string& filename) const {
    std::ofstream ofs(filename);
    serializeTo(ofs);
  }

  void serializeTo(std::ostream& to) const {
    to << n_ << "\n" << k_ << "\n";
    for (auto p : machines_) {
      to << p.first << "\t" << p.second << "\n";
    }
  }

  void deserializeFrom(std::istream& from) {
    machines_.clear();
    from >> n_;
    from >> k_;
    std::string line;
    while (std::getline(from, line)) {
      std::istringstream iss(line);
      HashCode pos;
      MachineId machine;
      iss >> pos;
      iss >> machine;
      machines_[pos] = machine;
    }
  }

  // Output data migration steps
  std::vector<DataMigrationStep> addMachine(MachineId id) {
    auto bySource = std::unordered_map<MachineId, std::vector<HashCodeRange> >();
    HashCode added = 0U;

    while (added < k_) {
      auto pos = randomGen_.generate() % n_;
      if (machines_.find(pos) == machines_.end()) {
        added += 1;
        machines_[pos] = id;

        auto it = machines_.find(pos);
        auto nextIt = next(it);
        if (nextIt == machines_.end()) nextIt = machines_.begin();
        MachineId src = nextIt->second;
        if (src != id) {
          auto prevIt = it == machines_.begin() ? prev(machines_.end()) : prev(it);
          bySource[src].push_back({ prevIt->first + 1, pos });
        }
      }
    }

    auto steps = std::vector<DataMigrationStep>();
    const auto dest = id;
    auto byStart = [](const HashCodeRange& a, const HashCodeRange& b) -> bool {
      return a.start < b.start;
    };
    auto sumLength = [](const HashCode& sofar, const HashCodeRange& cur) -> const HashCode {
      return sofar + (cur.end - cur.start + 1);
    };
    for (auto p : bySource) {
      const auto src = p.first;
      auto& ranges = p.second;
      std::sort(begin(ranges), end(ranges), byStart);

      HashCode totalLength = std::accumulate(begin(ranges), end(ranges), 0U, sumLength);
      steps.push_back({ src, dest, std::move(ranges), totalLength });
    }

    auto bySrc = [](const DataMigrationStep& a, const DataMigrationStep& b) -> bool {
      return a.src < b.src;
    };
    sort(begin(steps), end(steps), bySrc);
    return steps;
  }

  MachineId getMachineIdByHashCode(HashCode hashcode) {
    if (machines_.begin() == machines_.end()) return -1;
    auto it = machines_.lower_bound(hashcode);
    if (it == machines_.end()) it = machines_.begin();
    return it->second;
  }
};
