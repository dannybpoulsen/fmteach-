
#include "ir/cfa.hpp"
#include "ir/expr.hpp"

#include "exercises_plug.hpp"
#include "setup.hpp"

#include <cstdint>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <iostream>

namespace FMTeach {
  namespace Exer3 {

    using namespace FMTeach::IR;
    struct Evaluator : private FMTeach::IR::ExprVisitor<std::int8_t> {
      Evaluator (const ExecutionState& s) : state (s) {}

      auto operator() (const Expr& e) {
	return visit(e);
      }

      virtual std::int8_t visitRegister (const Register& r) {
	return state.getRegisters ()[r.getNumber ()];
      }
      
      virtual std::int8_t visitConstant (const Constant& r) {
	return r.getValue ();
      }
      virtual std::int8_t visitAddExpr (const AddExpr& r) {
	return visit(r.getLeft ()) + visit(r.getRight ());
      }
      virtual std::int8_t visitSubExpr (const SubExpr& r) {
	return visit(r.getLeft ()) - visit(r.getRight ());
      
      }
      virtual std::int8_t visitDivExpr (const DivExpr& r) {
	return visit(r.getLeft ()) / visit(r.getRight ());
		
      }
      virtual std::int8_t visitMulExpr (const MulExpr& r) {
	return visit(r.getLeft ()) * visit(r.getRight ());
		
      }
      virtual std::int8_t visitLEqExpr (const LEqExpr& r) {
	return visit(r.getLeft ()) <= visit(r.getRight ());
      
      }
      virtual std::int8_t visitGEqExpr (const GEqExpr& r) {
	return visit(r.getLeft ()) >= visit(r.getRight ());
      
      }
      virtual std::int8_t visitNEqExpr (const NEqExpr& r) {
	return visit(r.getLeft ()) != visit(r.getRight ());
      
      }
      virtual std::int8_t visitEqExpr (const EqExpr& r) {
	return visit(r.getLeft ()) == visit(r.getRight ());
      
      }
      virtual std::int8_t visitLtExpr (const LtExpr& r) {
	return visit(r.getLeft ()) < visit(r.getRight ());
      
      }
      virtual std::int8_t visitGtExpr (const GtExpr& r) {
	return visit(r.getLeft ()) > visit(r.getRight ());
      
      }
      virtual std::int8_t visitNegationExpr (const NegationExpr& r) {
	return !(visit (r.getInner ()));
      }
      virtual std::int8_t visitMinusExpr (const MinusExpr& r) {
	return -(visit (r.getInner ()));
      }
      virtual std::int8_t visitDerefExpr (const DerefExpr& r) {
	auto addres = visit(r.getInner ());
	return state.getMemory ()[addres];
      }

      private:
      const ExecutionState& state;
    };


    bool execute (ExecutionState& state, Evaluator& eval, const FMTeach::IR::Instruction& instr) {	
      switch (instr.instType ()) {
      case FMTeach::IR::Assign::opcode (): { 
	auto& ass = static_cast<const FMTeach::IR::Assign&> (instr);
	state.getRegisters().set (ass.getDestination ().getNumber(),eval (ass.getExpression ()));
	return true;
	break;
      }
      case FMTeach::IR::Assume::opcode ():
	return eval (static_cast<const FMTeach::IR::Assume&> (instr).getExpression ());
	break;
      case FMTeach::IR::Skip::opcode ():
	
	return true;
      case FMTeach::IR::Store::opcode (): {
	  auto& st = static_cast<const FMTeach::IR::Store&> (instr);
	  state.getMemory ().set (eval (st.getAddress ()),eval (st.getStoree ()));
	  
	  return true;
	  break;
	    
	}	
      default:
	return false;
      }
    }


    class Executor : private FMTeach::IR::InstructionVisitor<bool> {
    public:
      Executor (ExecutionState& state) : state(state),eval(state) {}

      bool operator() (const Instruction& instr) {
	return visit (instr);
      }
      
      bool visitAssign (const Assign& ass)  {
	state.getRegisters().set (ass.getDestination ().getNumber(),eval (ass.getExpression ()));
	return true;
      }

      bool visitAssume (const Assume& ass) {
	return eval (ass.getExpression ());
      }

      bool visitSkip (const Skip&) {
	return true;
      }
      
      bool visitStore (const Store& st) {
	state.getMemory ().set (eval (st.getAddress ()),eval (st.getStoree ()));
	return true;
      }

    private:
      ExecutionState& state;
      Evaluator eval;
    };
    
    FMTeach::Result_ptr FMTeach::Exer3::InterpreterExer::teacher_solution (const FMTeach::IR::CFA& cfa) {
      
      ExecutionState state{cfa.getRegisters ().size(), 127, cfa.getInitial ()};
      Executor exec (state);
      bool ok = true;
      do {
	auto loc = state.getLocation ();
	auto& edges = loc->edges ();
	if (!edges.size ())
	  break;
	else { 
	  ok = false;
	  for (auto& e : loc->edges ()) {
	    ok = exec (*e.getInstruction ());
	    if (ok) {
	      state.setLocation (e.getTo ());
	      break;
	    }
	  
	  }

	}
      }while (ok);
      
      return std::make_unique<FMTeach::Exer3::ResultExer> (std::move(state));
    }
    
  }

}
