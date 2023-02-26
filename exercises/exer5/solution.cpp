
#include "ir/cfa.hpp"
#include "ir/expr.hpp"

#include "exercises_plug.hpp"
#include "setup.hpp"

#include <cstdint>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

namespace FMTeach {
namespace Exer5{

using namespace FMTeach::IR;
  
  struct Evaluator : private FMTeach::IR::ExprVisitor<Lattice> {
    Evaluator(const ExecutionState &s) : state(s) {}
    
    auto operator()(const Expr &e) { return visit(e); }
    
    virtual Lattice visitRegister(const Register &r) {
      return state.getRegisters()[r.getNumber()];
    }
    
    virtual Lattice visitConstant(const Constant &r) {
      if (r.getValue () == 0)
	return {Lattice::AbsValue::Zero};
      else if (r.getValue () < 0) {
	return {Lattice::AbsValue::Negative};	
      }
      else {
	return {Lattice::AbsValue::Pos};	
      }
    }
    
    virtual Lattice visitAddExpr(const AddExpr &r) {
      static Lattice::AbsValue operations [4][4] = {
	{Lattice::AbsValue::Zero,    Lattice::AbsValue::Pos, Lattice::AbsValue::Negative,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Pos,     Lattice::AbsValue::Pos, Lattice::AbsValue::Top,     Lattice::AbsValue::Top},
	{Lattice::AbsValue::Negative,Lattice::AbsValue::Top, Lattice::AbsValue::Negative,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,     Lattice::AbsValue::Top, Lattice::AbsValue::Top,     Lattice::AbsValue::Top}
      };
      auto left = visit (r.getLeft ());
      auto right = visit (r.getRight ());
      return {operations[static_cast<int> (left.getValue())][static_cast<int> (right.getValue())]};
      
    }
    virtual Lattice visitSubExpr(const SubExpr &r) {
      static Lattice::AbsValue operations [4][4] = {
	{Lattice::AbsValue::Zero,    Lattice::AbsValue::Negative, Lattice::AbsValue::Pos,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Pos,     Lattice::AbsValue::Top,      Lattice::AbsValue::Pos,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Negative,Lattice::AbsValue::Pos,      Lattice::AbsValue::Top,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,     Lattice::AbsValue::Top,      Lattice::AbsValue::Top, Lattice::AbsValue::Top}
      };
      auto left = visit (r.getLeft ());
      auto right = visit (r.getRight ());
      return {operations[static_cast<int> (left.getValue())][static_cast<int> (right.getValue())]};
      

    }
    virtual Lattice visitDivExpr(const DivExpr &r) {
      static Lattice::AbsValue operations [4][4] = {
	{Lattice::AbsValue::Top,    Lattice::AbsValue::Zero, Lattice::AbsValue::Zero,Lattice::AbsValue::Zero},
	{Lattice::AbsValue::Top,    Lattice::AbsValue::Pos,      Lattice::AbsValue::Negative,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,     Lattice::AbsValue::Negative,      Lattice::AbsValue::Pos,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,     Lattice::AbsValue::Top,      Lattice::AbsValue::Top, Lattice::AbsValue::Top}
      };
      auto left = visit (r.getLeft ());
      auto right = visit (r.getRight ());
      return {operations[static_cast<int> (left.getValue())][static_cast<int> (right.getValue())]};
      
    }

    virtual Lattice visitMulExpr(const MulExpr &r) {
      static Lattice::AbsValue operations [4][4] = {
	{Lattice::AbsValue::Zero,    Lattice::AbsValue::Zero, Lattice::AbsValue::Zero,Lattice::AbsValue::Zero},
	{Lattice::AbsValue::Zero,    Lattice::AbsValue::Pos,      Lattice::AbsValue::Negative,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Zero,     Lattice::AbsValue::Negative,      Lattice::AbsValue::Pos,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Zero,     Lattice::AbsValue::Top,      Lattice::AbsValue::Top, Lattice::AbsValue::Top}
      };
      auto left = visit (r.getLeft ());
      auto right = visit (r.getRight ());
      return {operations[static_cast<int> (left.getValue())][static_cast<int> (right.getValue())]};
      
    }

    virtual Lattice visitLEqExpr(const LEqExpr &r) {
      static Lattice::AbsValue operations [4][4] = {
	{Lattice::AbsValue::Top,    Lattice::AbsValue::Top,       Lattice::AbsValue::Zero,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Zero,    Lattice::AbsValue::Top,      Lattice::AbsValue::Top,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,     Lattice::AbsValue::Top,      Lattice::AbsValue::Top,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,     Lattice::AbsValue::Top,      Lattice::AbsValue::Top, Lattice::AbsValue::Top}
      };
      auto left = visit (r.getLeft ());
      auto right = visit (r.getRight ());
      return {operations[static_cast<int> (left.getValue())][static_cast<int> (right.getValue())]};
      
    }
    
    virtual Lattice visitGEqExpr(const GEqExpr &r) {
      static Lattice::AbsValue operations [4][4] = {
	{Lattice::AbsValue::Top,    Lattice::AbsValue::Zero,      Lattice::AbsValue::Top,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,    Lattice::AbsValue::Top,      Lattice::AbsValue::Top,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Zero,   Lattice::AbsValue::Zero,     Lattice::AbsValue::Top,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,    Lattice::AbsValue::Top,      Lattice::AbsValue::Top, Lattice::AbsValue::Top}
      };
      auto left = visit (r.getLeft ());
      auto right = visit (r.getRight ());
      return {operations[static_cast<int> (left.getValue())][static_cast<int> (right.getValue())]};
      
    }

    virtual Lattice visitNEqExpr(const NEqExpr &r) {
      static Lattice::AbsValue operations [4][4] = {
	{Lattice::AbsValue::Zero,  Lattice::AbsValue::Top,      Lattice::AbsValue::Top,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,   Lattice::AbsValue::Top,      Lattice::AbsValue::Top,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,   Lattice::AbsValue::Top,      Lattice::AbsValue::Top,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,   Lattice::AbsValue::Top,      Lattice::AbsValue::Top, Lattice::AbsValue::Top}
      };
      auto left = visit (r.getLeft ());
      auto right = visit (r.getRight ());
      return {operations[static_cast<int> (left.getValue())][static_cast<int> (right.getValue())]};
      
    }

    virtual Lattice visitEqExpr(const EqExpr &r) {
      static Lattice::AbsValue operations [4][4] = {
	{Lattice::AbsValue::Top,  Lattice::AbsValue::Zero,      Lattice::AbsValue::Zero,Lattice::AbsValue::Top},
	{Lattice::AbsValue::Zero, Lattice::AbsValue::Top,      Lattice::AbsValue::Zero, Lattice::AbsValue::Top},
	{Lattice::AbsValue::Zero, Lattice::AbsValue::Zero,      Lattice::AbsValue::Top,  Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,  Lattice::AbsValue::Top,      Lattice::AbsValue::Top,  Lattice::AbsValue::Top}
      };
      auto left = visit (r.getLeft ());
      auto right = visit (r.getRight ());
      return {operations[static_cast<int> (left.getValue())][static_cast<int> (right.getValue())]};
      
    }

    virtual Lattice visitLtExpr(const LtExpr &r) {
      static Lattice::AbsValue operations [4][4] = {
	{Lattice::AbsValue::Zero, Lattice::AbsValue::Top,    Lattice::AbsValue::Zero, Lattice::AbsValue::Top},
	{Lattice::AbsValue::Zero, Lattice::AbsValue::Top,    Lattice::AbsValue::Zero, Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top, Lattice::AbsValue::Top,     Lattice::AbsValue::Top,  Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,  Lattice::AbsValue::Top,    Lattice::AbsValue::Top,  Lattice::AbsValue::Top}
      };
      auto left = visit (r.getLeft ());
      auto right = visit (r.getRight ());
      return {operations[static_cast<int> (left.getValue())][static_cast<int> (right.getValue())]};
      
    }

    virtual Lattice visitGtExpr(const GtExpr &r) {
      static Lattice::AbsValue operations [4][4] = {
	{Lattice::AbsValue::Zero, Lattice::AbsValue::Zero,    Lattice::AbsValue::Top, Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top, Lattice::AbsValue::Top,    Lattice::AbsValue::Top, Lattice::AbsValue::Top},
	{Lattice::AbsValue::Zero, Lattice::AbsValue::Zero,     Lattice::AbsValue::Top,  Lattice::AbsValue::Top},
	{Lattice::AbsValue::Top,  Lattice::AbsValue::Top,    Lattice::AbsValue::Top,  Lattice::AbsValue::Top}
      };
      auto left = visit (r.getLeft ());
      auto right = visit (r.getRight ());
      return {operations[static_cast<int> (left.getValue())][static_cast<int> (right.getValue())]};
      
    }

    virtual Lattice visitNegationExpr(const NegationExpr &r) {
      static Lattice::AbsValue operations [4] = {
	Lattice::AbsValue::Top, Lattice::AbsValue::Zero,    Lattice::AbsValue::Zero, Lattice::AbsValue::Top
      };
      return {operations[static_cast<int> (visit (r.getInner ()).getValue  ())]};
    }

    virtual Lattice visitMinusExpr(const MinusExpr &r) {
        static Lattice::AbsValue operations [4] = {
	  Lattice::AbsValue::Zero, Lattice::AbsValue::Negative,    Lattice::AbsValue::Pos, Lattice::AbsValue::Top
	};
	return {operations[static_cast<int> (visit(r.getInner ()).getValue  ())]};
	
    }

    virtual Lattice visitDerefExpr(const DerefExpr &r) {
      return {Lattice::AbsValue::Top};
    }
    
  private:
    const ExecutionState &state;
			};
  
  class Executor : private FMTeach::IR::InstructionVisitor<std::vector<ExecutionState>> {
  public:
    Executor(const ExecutionState& state) : state(state), eval(state) {}
    
    std::vector<ExecutionState> operator()(const FMTeach::IR::Edge& e) {
      goal = e.getTo ();
      return visit(*e.getInstruction ());
    }
    
    std::vector<ExecutionState> visitAssign(const Assign &ass) {
      ExecutionState stt {state};
      stt.setLocation (goal);
      
      stt.getRegisters().set(ass.getDestination().getNumber(),
			       eval(ass.getExpression()));
      return {stt};
    }
    
    std::vector<ExecutionState> visitAssume(const Assume &ass) {
      ExecutionState stt {state};
      stt.setLocation (goal);
      if (eval(ass.getExpression()).isZero ()) {
	return {};
      }
      else return {stt};
    }
    
    std::vector<ExecutionState> visitSkip(const Skip &) {
      ExecutionState stt {state};
      stt.setLocation (goal);
      return {stt};
    }
    
    std::vector<ExecutionState> visitStore(const Store &st) {
      ExecutionState stt {state};
      stt.setLocation (goal);
      return {stt};
    }
    
    std::vector<ExecutionState> visitNonDetAssign(const NonDetAssign& ass ) {
     
      ExecutionState stt {state};
      stt.setLocation (goal);
      stt.getRegisters().set(ass.getDestination().getNumber(),{Lattice::AbsValue::Top});
      
      return {stt};
    }
    
  private:
    const ExecutionState& state;
    Evaluator eval;
    FMTeach::IR::Location_ptr goal;
  };


  bool coveredBy (const ExecutionState& l,const ExecutionState& r) {

    auto check = [](auto& vecl,auto& vec2l) {
      auto lit = vecl.begin();
      auto rit = vec2l.begin();
      
      for (; lit != vecl.end(); ++lit, ++rit) {
	if (*rit < *lit ) {
	  return false;
	}
      }
      return true;
    };
    
    return l.getLocation () == r.getLocation () &&
      check (l.getRegisters(),r.getRegisters ()) &&
      check (l.getMemory (),r.getMemory ());
      
  }
  
  FMTeach::Result_ptr
  FMTeach::Exer5::AInterExer::teacher_solution(const FMTeach::IR::CFA &cfa) {
    ExecutionState state{cfa.getRegisters().size(), 127, cfa.getInitial()};
    std::vector<ExecutionState> violations;
    
    std::vector<ExecutionState> waiting;
    std::unordered_set<ExecutionState> passed;


    auto alreadyExplored = [&passed] (auto&state) {
      for (auto& s : passed) {
	if (coveredBy (state,s)) {
	  return true;
	}
      }
      return false;
    };
    
    waiting.push_back (state);
    while (waiting.size ()) {
      auto cur = waiting.back ();
      cur.output (std::cerr) << std ::endl;; 
      
      waiting.pop_back ();
      Executor exec{cur};
      
      for (auto& e  : cur.getLocation ()->edges ()) {
	for (auto& succ : exec(e)) {
	  
	  if (!alreadyExplored (succ)) {
	    if (succ.getLocation ()->isAssert ()) {
	      violations.push_back (succ);
	    }
	    else {
	      passed.insert(succ);  
	      waiting.push_back (std::move(succ));
	    }
	  }

	  
	}
	
      }
    }
    
    return std::make_unique<FMTeach::Exer5::ResultExer>(std::move(violations));
  }
  
  } // namespace Exer4
  
} // namespace FMTeach

