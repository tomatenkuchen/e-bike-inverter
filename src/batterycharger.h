#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define BATTERYCHARGER_EXPORT __declspec(dllexport)
#else
  #define BATTERYCHARGER_EXPORT
#endif

BATTERYCHARGER_EXPORT void batterycharger();
BATTERYCHARGER_EXPORT void batterycharger_print_vector(const std::vector<std::string> &strings);
