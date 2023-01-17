#include "whiley/ast.hpp"


namespace FMTeach {
  namespace Whiley {
    class WParser {
    public:
   
      Program parse( const std::string& filename );
      Program parse( std::istream& iss );
    };
  }
}
