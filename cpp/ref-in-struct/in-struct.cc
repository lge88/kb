#include <string>
#include <iostream>

struct FKV {
  std::string* txtVal = nullptr;
  uint64_t iVal = 0U;
};

int main(int argc, char* argv[]) {
  FKV f;
  std::cout << f.iVal << "\n";
  std::cout << f.txtVal << "\n";
  return 0;
}
