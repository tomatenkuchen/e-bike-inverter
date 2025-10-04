#include "batterycharger.h"
#include "version.hpp"
#include <string>
#include <vector>

int main() {
  batterycharger();

  std::vector<std::string> vec;
  vec.push_back("test_package");

  batterycharger_print_vector(vec);
}
