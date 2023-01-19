

#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include <cstdint>
#include <ostream>

namespace FMTeach {

  namespace Exer1 {

    class EnumStatesExer : public FMTeach::Exercise  {
    public:
      EnumStatesExer () : Exercise ("CFA") {}
      FMTeach::Result_ptr teacher_solution (const FMTeach::IR::CFA&) override;
      FMTeach::Result_ptr student_solution (const FMTeach::IR::CFA&) override;
      
      
    private:
      
    };

    class ResultExer : public FMTeach::Result  {
    public:
      ResultExer (std::size_t i) : numberOfLocations (i) {}
      std::ostream& writeResult ( std::ostream& os) override {
	return os << "Number of locations: " << numberOfLocations << std::endl;
      }
      
    private:
      std::size_t numberOfLocations;
      
    };
  }
}
    
