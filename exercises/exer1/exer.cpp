#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include "setup.hpp"
#include <cstdint>

namespace FMTeach {
  namespace Exer1 {

    FMTeach::Result_ptr FMTeach::Exer1::EnumStatesExer::student_solution (const FMTeach::IR::CFA&)  {
      throw NotSolvedYet (__FILE__);  
      return std::make_unique<FMTeach::Exer1::ResultExer> (0);
    }
  }

}

namespace {
  static FMTeach::Exer1::EnumStatesExer exer;
}
