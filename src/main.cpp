#include "batterycharger.h"
#include <vector>
#include <string>

int main() {
    batterycharger();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    batterycharger_print_vector(vec);
}
