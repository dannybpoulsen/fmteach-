#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include "setup.hpp"
#include <cstdint>

namespace FMTeach {
  namespace Exer3 {

    FMTeach::Result_ptr FMTeach::Exer3::InterpreterExer::student_solution (const FMTeach::IR::CFA& cfa)  {
      throw NotSolvedYet (__FILE__);
      ExecutionState state{cfa.getRegisters ().size (), 127, cfa.getInitial () };
	return std::make_unique<FMTeach::Exer3::ResultExer> (std::move(state));
    }
  }

}

namespace {
  static FMTeach::Exer3::InterpreterExer exer;
}
