

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
#include <functional>
#include <unordered_set>



namespace FMTeach {

  namespace Exer4 {

    using ExecutionState = ExecState<Value<std::int8_t>>;
    
    class InitialisedExer : public FMTeach::Exercise  {
    public:
      InitialisedExer () : Exercise ("ExplicitMC") {}
      FMTeach::Result_ptr teacher_solution (const FMTeach::IR::CFA&) override;
      FMTeach::Result_ptr student_solution (const FMTeach::IR::CFA&) override;
      
      
    };

    class ResultExer : public FMTeach::Result  {
    public:
      ResultExer (std::vector<ExecutionState>&& s) : violations(std::move(s)) {}
      std::ostream& writeResult ( std::ostream& os) override {
	return os << "Found " << violations.size () << " assert vioations" << std::endl;
      }
      
    private:
      std::vector<ExecutionState> violations;
    };
  }
} // namespace FMTeach    
