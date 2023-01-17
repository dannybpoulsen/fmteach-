
#include "ir/cfa.hpp"
#include "exercises_plug.hpp"

#include <cstdint>
#include <unordered_set>
#include <vector>

namespace FMTeach {
  namespace Exer1 {
    std::int64_t enum_cfa_loca_sol (const FMTeach::IR::CFA& cfa) {
      std::unordered_set<FMTeach::IR::Location_ptr> passed;
      std::vector<FMTeach::IR::Location_ptr> waiting;
      
      waiting.push_back (cfa.getInitial ());
      passed.insert  (cfa.getInitial ());
      while (waiting.size ()) {
	auto cur = waiting.back ();
	waiting.pop_back ();
	for (auto& e : cur->edges ()) {
	  if (!passed.count (e.getTo ())) {
	    passed.insert (e.getTo ());
	    waiting.push_back (e.getTo ());
	  }
	}
      }
      

      return passed.size ();
    }
    
  }

}
