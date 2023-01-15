#include "whiley/parser.hpp"
#include "scanner.h"
#include "parser.hh"

#include <iostream>

namespace FMTeach {
  namespace Whiley {
    void WParser::parse( std::istream &iss ) {
      Scanner scanner {&iss};
      Parser parser{scanner};

      if (!parser.parse ()) {
	std::cerr << "Parse Failed" << std::endl;
      }
    }
  }
}
