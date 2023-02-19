

#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include "execstate.hpp"
#include <cstdint>
#include <ostream>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <cassert>

namespace FMTeach {

  namespace Exer3 {

    class InterpreterExer : public FMTeach::Exercise  {
    public:
      InterpreterExer () : Exercise ("Interpreter") {}
      FMTeach::Result_ptr teacher_solution (const FMTeach::IR::CFA&) override;
      FMTeach::Result_ptr student_solution (const FMTeach::IR::CFA&) override;
      

    };

    using ExecutionState = ExecState<Value<std::int8_t>>;
    
    class ResultExer : public FMTeach::Result  {
    public:
      ResultExer (ExecutionState&& state) :state(std::move(state))   {}
      std::ostream& writeResult ( std::ostream& os) override {
	return state.output (os) << std::endl;
      }
      private:
      ExecutionState state;
    };
  }
}
    
