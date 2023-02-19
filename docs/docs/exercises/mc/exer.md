## Exercise 4 
In this exercise the end goal is to implement an Explicit State Reachability algorithm for Whiley.   
Your implementation should be added to `exercises/exer4.cpp`, and you can probably big parts of your solution ot exercise 3.
``` C++
#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include "setup.hpp"
#include <cstdint>
#include <unordered_set>

namespace FMTeach {
  namespace Exer4 {

    FMTeach::Result_ptr FMTeach::Exer4::InitialisedExer::student_solution (const FMTeach::IR::CFA& cfa)  {
      std::vector<ExecutionState> violations;// (2)
      ExecutionState state{cfa.getRegisters ().size (), 127, cfa.getInitial () }; // (1)
      throw NotSolvedYet (__FILE__);
	  return std::make_unique<FMTeach::Exer4::ResultExer> (std::move(violations));
    }
  }

}

namespace {
  static FMTeach::Exer4::InitialisedExer exer;
}

```

1. The initial state of a Whiley program. You probably want to look at the file `exercises/exer4/setup.hpp` and `exercises/execstate/execstate.hpp"` for how the state is represented 
2. Vector of states you found violating an assert. You can check if a CFA location is an error state with `succ.getLocation ()->isAssert ()`. It will return `true` if the location an error location.




