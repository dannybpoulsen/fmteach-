#include "whiley/parser.hpp"
#include <iostream>

int main () {
  FMTeach::Whiley::WParser parser;
  auto prgm = parser.parse (std::cin);
  std::cerr << prgm << std::endl;
}

