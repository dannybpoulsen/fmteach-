#include "ir/cfa.hpp"
#include "exercises_plug.hpp"

#include <cstdint>

namespace FMTeach {
  namespace Exer1 {
    std::int64_t enum_cfa_loca_sol (const FMTeach::IR::CFA&);
    
    std::int64_t enum_cfa_loca (const FMTeach::IR::CFA&) {
      throw NotSolvedYet (__FILE__);
    }
    
  }

}

namespace {
  static FMTeach::Exercise exer {"cfa",FMTeach::Exer1::enum_cfa_loca_sol,FMTeach::Exer1::enum_cfa_loca};
}
