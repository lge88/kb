#include <cstdint>
#include <string>
#include <vector>

#include <sys/uio.h>

enum MsgType : uint8_t {
  GET = 0,
  PUT
};

static const uint8_t MsgTypes[2] = {
  GET,
  PUT
};

template<typename T>
struct serializable {
  static const bool value = false;
};

struct MsgGet {
  std::string key_;
  void serialize(std::vector<iovec>& iovecList) const {
    iovec v1 = { (void *)(&MsgTypes[0]), 1U };
    iovec v2 = { (void *)(key_.c_str()), key_.size() };
    iovecList.push_back(std::move(v1));
    iovecList.push_back(std::move(v2));
    // iovecList.emplace_back(key_.c_str(), key_.size());
  }
};

template<>
struct serializable<MsgGet> {
  static const bool value = true;
};

// struct MsgPut {
//   std::string key_, val_;
//   vector<iovec> serialize() const {
//     iovecList.emplace_back((void *)&MsgTypes[0], 1U);
//     iovecList.emplace_back(key_.c_str(), key_.size());
//     iovecList.emplace_back(val_.c_str(), val_.size());
//   }
// };

// template<>
// struct serializable<MsgPut> {
//   static const bool value = true;
// }
