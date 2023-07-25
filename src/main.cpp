#include <fmt/core.h>

#include <iostream>

#include "version.h"

int main() {
  fmt::print("Hello, World! from VERSION {}\n",
               HelloWorldProject_VERSION_STRING);
  std::cin.ignore();
  return 0;
}
