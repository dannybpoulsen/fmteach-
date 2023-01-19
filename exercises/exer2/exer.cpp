#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include "setup.hpp"
#include <cstdint>

namespace FMTeach {
  namespace Exer2 {

    FMTeach::Result_ptr FMTeach::Exer2::CFAVisualiseExer::student_solution (const FMTeach::IR::CFA&)  {
      throw NotSolvedYet (__FILE__);  
      Graph g;
      return std::make_unique<FMTeach::Exer2::ResultExer> (std::move(g));
    }
  }

}

namespace {
  static FMTeach::Exer2::CFAVisualiseExer exer;
}
