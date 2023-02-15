## Exercise 3 
In this exercise the end goal is to have a concrete interpreter for Whiley --- that is we should be able to execute a (closed) program written in whiley. 
Your implementation should be added to `exercises/exer3.cpp`
``` C++
#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include "setup.hpp"
#include <cstdint>

namespace FMTeach {
  namespace Exer3 {

    FMTeach::Result_ptr FMTeach::Exer3::InterpreterExer::student_solution (const FMTeach::IR::CFA& cfa)  {
      ExecutionState state{cfa.getRegisters ().size (), 127, cfa.getInitial () }; // (1) 
	  throw NotSolvedYet (__FILE__);    // (2)
	  return std::make_unique<FMTeach::Exer3::ResultExer> (std::move(state)); 
     }
  }

}

namespace {
  static FMTeach::Exer3::InterpreterExer exer;
}
```

1. The initial state of a Whiley program. You probably want to look at the file `exercises/exer3/setup.hpp` for how the state is represented 
2. Replace this line with your solution


## Visitors 
To help you implement your interpreter both IR expressions and IR Instruction have a visitor pattern implemented. Look inside `libs/ir/include/instructions.hpp` and  `libs/ir/include/expr.hpp` to see their definitions.

## Solution Sketch




