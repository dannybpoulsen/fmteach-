
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
namespace Exer4 {

using namespace FMTeach::IR;

  struct Evaluator : private FMTeach::IR::ExprVisitor<Value<std::int8_t>> {
  Evaluator(const ExecutionState &s) : state(s) {}

  auto operator()(const Expr &e) { return visit(e); }

  virtual Value<std::int8_t> visitRegister(const Register &r) {
    return state.getRegisters()[r.getNumber()];
  }

  virtual Value<std::int8_t> visitConstant(const Constant &r) { return r.getValue(); }
  virtual Value<std::int8_t> visitAddExpr(const AddExpr &r) {
    return visit(r.getLeft()) + visit(r.getRight());
  }
  virtual Value<std::int8_t> visitSubExpr(const SubExpr &r) {
    return visit(r.getLeft()) - visit(r.getRight());
  }
  virtual Value<std::int8_t> visitDivExpr(const DivExpr &r) {
    return visit(r.getLeft()) / visit(r.getRight());
  }
  virtual Value<std::int8_t> visitMulExpr(const MulExpr &r) {
    return visit(r.getLeft()) * visit(r.getRight());
  }
  virtual Value<std::int8_t> visitLEqExpr(const LEqExpr &r) {
    return visit(r.getLeft()) <= visit(r.getRight());
  }
  virtual Value<std::int8_t> visitGEqExpr(const GEqExpr &r) {
    return visit(r.getLeft()) >= visit(r.getRight());
  }
  virtual Value<std::int8_t> visitNEqExpr(const NEqExpr &r) {
    return visit(r.getLeft()) != visit(r.getRight());
  }
  virtual Value<std::int8_t> visitEqExpr(const EqExpr &r) {
    return visit(r.getLeft()) == visit(r.getRight());
  }
  virtual Value<std::int8_t> visitLtExpr(const LtExpr &r) {
    return visit(r.getLeft()) < visit(r.getRight());
  }
  virtual Value<std::int8_t> visitGtExpr(const GtExpr &r) {
    return visit(r.getLeft()) > visit(r.getRight());
  }
  virtual Value<std::int8_t> visitNegationExpr(const NegationExpr &r) {
    return !(visit(r.getInner()));
  }
  virtual Value<std::int8_t> visitMinusExpr(const MinusExpr &r) {
    return -(visit(r.getInner()));
  }
  virtual Value<std::int8_t> visitDerefExpr(const DerefExpr &r) {
    auto addres = visit(r.getInner());
    return state.getMemory()[addres];
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
      if (eval(ass.getExpression()))
	return {stt};
      else return {};
    }
    
    std::vector<ExecutionState> visitSkip(const Skip &) {
      ExecutionState stt {state};
      stt.setLocation (goal);
      return {stt};
    }
    
    std::vector<ExecutionState> visitStore(const Store &st) {
      ExecutionState stt {state};
      stt.setLocation (goal);
      stt.getMemory().set(eval(st.getAddress()), eval(st.getStoree()));
      return {stt};
    }
    
    std::vector<ExecutionState> visitNonDetAssign(const NonDetAssign& ass ) {
      std::vector<ExecutionState> buf;
      
      for (std::int8_t i = std::numeric_limits<std::int8_t>::min (); i < std::numeric_limits<std::int8_t>::max (); ++i) {
	ExecutionState stt {state};
	stt.setLocation (goal);
	stt.getRegisters().set(ass.getDestination().getNumber(),i);
	assert(stt.hash () != state.hash ());
	buf.push_back (std::move(stt));
      }
      
      return buf;
    }
    
  private:
    const ExecutionState& state;
    Evaluator eval;
    FMTeach::IR::Location_ptr goal;
  };

  FMTeach::Result_ptr
  FMTeach::Exer4::InitialisedExer::teacher_solution(const FMTeach::IR::CFA &cfa) {
    ExecutionState state{cfa.getRegisters().size(), 127, cfa.getInitial()};
    std::vector<ExecutionState> violations;
    
    std::vector<ExecutionState> waiting;
    std::unordered_set<ExecutionState> passed;
    
    waiting.push_back (state);
    passed.insert(state);
    while (waiting.size ()) {
      auto cur = waiting.back ();
      waiting.pop_back ();
      Executor exec{cur};
      
      for (auto& e  : cur.getLocation ()->edges ()) {
	for (auto& succ : exec(e)) {
	  
	  if (!passed.count (succ)) {
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
    
    return std::make_unique<FMTeach::Exer4::ResultExer>(std::move(violations));
  }
  
  } // namespace Exer4
  
} // namespace FMTeach
