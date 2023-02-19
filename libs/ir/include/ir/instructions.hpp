

#ifndef _IR_INSTRUCTIONS__
#define _IR_INSTRUCTIONS__

#include "ir/expr.hpp"
#include <ostream>
#include <memory>
#include <cstdint>

namespace FMTeach {
  namespace IR {
    
    using instrtype_t = std::size_t;
    
    class Instruction {
    public:
      virtual std::ostream& output(std::ostream&) const = 0;
      auto instType () const {return type;}

    protected:
      Instruction (instrtype_t t) : type(t) {}
      
      
      private:
      instrtype_t type;
      
    };

    inline std::ostream& operator<< (std::ostream& os, const Instruction& inst) {
      return inst.output (os);
    }
    
    using Instruction_ptr = std::shared_ptr<Instruction>;
    
    class Assign : public Instruction {
    public:
      Assign (Register_ptr dest, Expr_ptr expr);
      static consteval instrtype_t opcode () ;
      auto& getDestination () const {return *assignee;}
      auto& getExpression () const {return *expr;}
      std::ostream& output(std::ostream&) const override;
      
    private:
      Register_ptr assignee;
      Expr_ptr expr;
    };

    class NonDetAssign : public Instruction {
    public:
      NonDetAssign (Register_ptr dest);
      static consteval instrtype_t opcode () ;
      auto& getDestination () const {return *assignee;}
      std::ostream& output(std::ostream&) const override;
      
    private:
      Register_ptr assignee;
    };
    
    
    class Assume : public Instruction {
    public:
      Assume (Expr_ptr expr);
      static consteval instrtype_t opcode () ;
      auto& getExpression () const {return *expr;}
      std::ostream& output(std::ostream&) const override;
      
      
    private:
      Expr_ptr expr;
      
    };

    class Skip : public Instruction {
    public:
      Skip ();
      static consteval instrtype_t opcode () ;
      std::ostream& output(std::ostream&) const override;
	
    };

    class Load : public Instruction {
    public:
      Load (Register_ptr dest, Expr_ptr address);
      static consteval instrtype_t opcode () ;
      auto& getDestination () const {return *assignee;}
      auto& getAddress () const {return *address;}
      std::ostream& output(std::ostream&) const override;
      
    private:
      Register_ptr assignee;
      Expr_ptr address;
    
    };
    
    class Store : public Instruction {
    public:
      Store (Expr_ptr toStore, Expr_ptr address);
      static consteval instrtype_t opcode () ;
      auto& getStoree () const {return *storee;}
      auto& getAddress () const {return *address;}
      std::ostream& output(std::ostream&) const override;
      
    private:
      Expr_ptr storee;
      Expr_ptr address;
    
    };

    template<class T>
    constexpr auto findInstrIndex () {
      return auto_index<0,T,Assign,Skip,Load,Store,Assume,NonDetAssign> (); 
    }

    consteval instrtype_t Assign::opcode () {return findInstrIndex<Assign> ();}
    consteval instrtype_t Assume::opcode () {return findInstrIndex<Assume> ();}
    consteval instrtype_t Skip::opcode () {return findInstrIndex<Skip> ();}
    consteval instrtype_t Store::opcode () {return findInstrIndex<Store> ();}
    consteval instrtype_t NonDetAssign::opcode () {return findInstrIndex<NonDetAssign> ();}
    
    
    template<class T>
    class InstructionVisitor {
    public:
      virtual T visitAssign (const Assign&) = 0;
      virtual T visitAssume (const Assume&) = 0;
      virtual T visitSkip (const Skip&) = 0;
      virtual T visitStore (const Store&) = 0;
      virtual T visitNonDetAssign (const NonDetAssign&) = 0;
      
    protected:
      T visit (const Instruction& instr) {
	switch (instr.instType ()) {
	case Assign::opcode ():
	  return visitAssign (static_cast<const Assign&> (instr));
	case Assume::opcode ():
	  return visitAssume (static_cast<const Assume&> (instr));
	case Skip::opcode ():
	  return visitSkip (static_cast<const Skip&> (instr));
	case Store::opcode ():
	  return visitStore (static_cast<const Store&> (instr));
	case NonDetAssign::opcode ():
	  return visitNonDetAssign (static_cast<const NonDetAssign&> (instr));
	
	default:
	  throw std::runtime_error ("Error");
	}
      }
    };
    
  }
}


#endif
