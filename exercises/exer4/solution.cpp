
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
  namespace Exer4 {

    using namespace FMTeach::IR;
    struct Evaluator : private FMTeach::IR::ExprVisitor<std::unordered_set<const Register*>> {
      Evaluator (const ExecutionState& s) : state (s) {}

      auto operator() (const Expr& e) {
	return visit(e);
      }

      virtual std::unordered_set<const Register*> visitRegister (const Register& r) {
	if (state.getRegisters()[r.getNumber()] == InitStatus::Uninitialised) {
	  return {&r};
	}
	else
	  return {}; 
      }
      
      virtual std::unordered_set<const Register*> visitConstant (const Constant& r) {
	return {};
      }

      virtual std::unordered_set<const Register*> visitAddExpr (const AddExpr& r) {
	return binHelper (r.getLeft (), r.getRight ());
      }
      
      virtual std::unordered_set<const Register*> visitSubExpr (const SubExpr& r) {
	return binHelper (r.getLeft (), r.getRight ());
      }

      virtual std::unordered_set<const Register*> visitDivExpr (const DivExpr& r) {
	return binHelper (r.getLeft (), r.getRight ());
      }

      virtual std::unordered_set<const Register*> visitMulExpr (const MulExpr& r) {
	return binHelper (r.getLeft (), r.getRight ());
      }
      virtual std::unordered_set<const Register*> visitLEqExpr (const LEqExpr& r) {
	return binHelper (r.getLeft (), r.getRight ());
      }
      virtual std::unordered_set<const Register*> visitGEqExpr (const GEqExpr& r) {
	return binHelper (r.getLeft (), r.getRight ());
      }
      virtual std::unordered_set<const Register*> visitNEqExpr (const NEqExpr& r) {
	return binHelper (r.getLeft (), r.getRight ());
      }
      virtual std::unordered_set<const Register*> visitEqExpr (const EqExpr& r) {
	return binHelper (r.getLeft (), r.getRight ());
      }
      virtual std::unordered_set<const Register*> visitLtExpr (const LtExpr& r) {
	return binHelper (r.getLeft (), r.getRight ());
      }
      virtual std::unordered_set<const Register*> visitGtExpr (const GtExpr& r) {
	return binHelper (r.getLeft (), r.getRight ());
      }
      virtual std::unordered_set<const Register*> visitNegationExpr (const NegationExpr& r) {
	return visit (r.getInner ()); 
      }

      virtual std::unordered_set<const Register*> visitMinusExpr (const MinusExpr& r) {
	return visit (r.getInner ());
      }
      virtual std::unordered_set<const Register*> visitDerefExpr (const DerefExpr& r) {
	return visit (r.getInner ());
      }

      private:
      std::unordered_set<const Register*> binHelper (const Expr& l, const Expr& r) {
	auto ll = visit (l);
	ll.merge (visit(r));
	return ll;
      }
      const ExecutionState& state;
    };


    
    class Executor : private FMTeach::IR::InstructionVisitor<bool> {
    public:
      Executor (ExecutionState& state,std::unordered_set<const Register*>& res) : state(state),eval(state),res(res) {}

      bool operator() (const Instruction& instr) {
	return visit (instr);
      }
      
      bool visitAssign (const Assign& ass)  {
	return true;
      }

      bool visitAssume (const Assume& ass) {
	return true;
      }

      bool visitSkip (const Skip&) {
	return true;
      }
      
      bool visitStore (const Store& st) {
	return true;
      }

    private:
      ExecutionState& state;
      Evaluator eval;
      std::unordered_set<const Register*>& res;
    };
    
    FMTeach::Result_ptr FMTeach::Exer4::InitialisedExer::teacher_solution (const FMTeach::IR::CFA& cfa) {
      std::unordered_set<const Register*> res;
      ExecutionState state{cfa.getRegisters ().size(),  cfa.getInitial ()};
      Executor exec (state,res);
      return std::make_unique<FMTeach::Exer4::ResultExer> ();
    }
    
  }

}
