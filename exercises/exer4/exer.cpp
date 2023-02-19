#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include "setup.hpp"
#include <cstdint>
#include <unordered_set>

namespace FMTeach {
  namespace Exer4 {

    FMTeach::Result_ptr FMTeach::Exer4::InitialisedExer::student_solution (const FMTeach::IR::CFA& cfa)  {
      throw NotSolvedYet (__FILE__);
      std::vector<ExecutionState> violations;
      std::unordered_set<const FMTeach::IR::Register*> found_uninitialised;
      ExecutionState state{cfa.getRegisters ().size (), 127, cfa.getInitial () };
      return std::make_unique<FMTeach::Exer4::ResultExer> (std::move(violations));
    }
  }

}

namespace {
  static FMTeach::Exer4::InitialisedExer exer;
}
