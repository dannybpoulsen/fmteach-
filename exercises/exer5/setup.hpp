

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

  namespace Exer5 {

    
    class Lattice {
    public:
      enum class AbsValue {
	Zero = 0,
	Pos = 1,
	Negative = 2,
	Top = 3
      };

      Lattice (AbsValue v) : val(v) {}
      Lattice () : val(AbsValue::Zero) {}
      
      
      auto getValue () const {return val;}
      std::size_t hash () const {return static_cast<std::size_t> (val);}
      
      std::ostream& output (std::ostream& os) const {
	switch (val) {
	case AbsValue::Zero:
	  return os << "0";
	case AbsValue::Pos:
	  return os << "+";
	case AbsValue::Negative:
	  return os << "-";
	case AbsValue::Top:
	  return os << "T";
	default:
	  __builtin_unreachable ();
	}
      }

      bool isZero () const {
	return val == AbsValue::Zero;
      }
      static Lattice defaultValue () {return AbsValue::Zero;}

      bool operator== (const Lattice& oth) const  {
	return val == oth.val;
      }
      
      bool operator!= (const Lattice& oth) const  {
	return val != oth.val;
      }

      bool operator< (const Lattice& oth) const  {
	if (oth.val == val)
	  return false;
	else if (oth.val == AbsValue::Top) {
	  return true;
	}

	else if (val == AbsValue::Zero) {
	  return true;
	}
	return false;
      }
      
      bool operator<= (const Lattice& oth) const  {
	return *this < oth ||
	  *this == oth;
      }
      
      static auto join (const Lattice& l, const Lattice& r) {
	if (l <= r) {
	  return r;
	}
	else if (r <= l) {
	  return l;
	}
	return Lattice {AbsValue::Top};
      }
      
    private:
      AbsValue val;
    };

    
    using ExecutionState = ExecState<Lattice>;
    
    class AInterExer : public FMTeach::Exercise  {
    public:
      AInterExer () : Exercise ("AbsInterpretation") {}
      FMTeach::Result_ptr teacher_solution (const FMTeach::IR::CFA&) override;
      FMTeach::Result_ptr student_solution (const FMTeach::IR::CFA&) override;
      
      
    };

    class ResultExer : public FMTeach::Result  {
    public:
      ResultExer (std::vector<ExecutionState>&& s) : violations(std::move(s)) {}
      std::ostream& writeResult ( std::ostream& os) override {
	os << "Found " << violations.size () << " violations" << std::endl;
	for (auto& s : violations) {
	  s.output (os) << std::endl << "============================" << std::endl;;
	  
	}
	return os;
      }
      
    private:
      std::vector<ExecutionState> violations;
    };
  }
} // namespace FMTeach    
