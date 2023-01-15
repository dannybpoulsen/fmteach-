#include <memory>

namespace FMTeach {
  namespace Whiley {
    class WParser {
    public:
   
      void parse( const char *filename );
      void parse( std::istream &iss );
    };
  }
}
