
#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include "setup.hpp"

#include <cstdint>
#include <unordered_set>
#include <vector>
#include <sstream>

namespace FMTeach {
  namespace Exer2 {
    FMTeach::Result_ptr FMTeach::Exer2::CFAVisualiseExer::teacher_solution (const FMTeach::IR::CFA& cfa) {
      Graph g;
      
      
      std::unordered_set<FMTeach::IR::Location_ptr> passed;
      std::vector<FMTeach::IR::Location_ptr> waiting;
      
      waiting.push_back (cfa.getInitial ());
      passed.insert  (cfa.getInitial ());
      while (waiting.size ()) {
	auto cur = waiting.back ();
	waiting.pop_back ();
	for (auto& e : cur->edges ()) {
	  std::stringstream str;
	  str << *e.getInstruction(); 
	  g.makeEdge (cur,e.getTo (),str.str());
	  if (!passed.count (e.getTo ())) {
	    passed.insert (e.getTo ());
	    waiting.push_back (e.getTo ());
	  }
	}
      }
      
      
      return std::make_unique<FMTeach::Exer2::ResultExer> (std::move(g));
    }
    
  }

}
