

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
      auto& getDestination () const {return *assignee;}
      auto& getExpression () const {return *expr;}
      std::ostream& output(std::ostream&) const override;
      
    private:
      Register_ptr assignee;
      Expr_ptr expr;
    };
    
    class Assume : public Instruction {
    public:
      Assume (Expr_ptr expr);
      auto& getExpression () const {return *expr;}
      std::ostream& output(std::ostream&) const override;
      
      
    private:
      Expr_ptr expr;
      
    };

    class Skip : public Instruction {
    public:
      Skip ();
      std::ostream& output(std::ostream&) const override;
	
    };

    class Load : public Instruction {
    public:
      Load (Register_ptr dest, Expr_ptr address);
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
      auto& getStoree () const {return *storee;}
      auto& getAddress () const {return *address;}
      std::ostream& output(std::ostream&) const override;
      
    private:
      Expr_ptr storee;
      Expr_ptr address;
    
    };
    
  }
}


#endif
