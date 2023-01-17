#include "whiley/parser.hpp"
#include "scanner.h"
#include "parser.hh"
#include "whiley/ast.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>

namespace FMTeach {
  namespace Whiley {
    Program  WParser::parse( std::istream& iss ) {
      ASTBuilder builder;
      Scanner scanner {&iss};
      
      Parser parser{scanner,builder};

      
      if (!parser.parse ()) {
	  return builder.get ();
      }

      else {
	throw std::runtime_error ("Parse Failed");
      
      }
      
    }

    Program WParser::parse(const std::string& s ) {
      std::ifstream ifs;

      ifs.open (s, std::ifstream::in);
      return parse (ifs);
    }
    
    
  }
}
