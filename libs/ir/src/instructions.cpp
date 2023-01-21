
#include "ir/instructions.hpp"

namespace FMTeach {
  namespace IR {

    template<class T>
    constexpr auto findInstrIndex () {
      return auto_index<0,T,Assign,Skip,Load,Store,Assume> (); 
    }
    
    
    Assign::Assign (Register_ptr dest, Expr_ptr expr) : Instruction (findInstrIndex<Assign> ()),
							assignee(dest),
							expr(expr) {}
    

    Assume::Assume (Expr_ptr expr) : Instruction (findInstrIndex<Assume> ()),
				     expr(expr) {}
    

    std::ostream& Assume::output (std::ostream& os) const  {
      return os << "Assume (" <<* expr <<") ";
    }
    
    std::ostream& Assign::output (std::ostream& os) const  {
      return os << *assignee <<" := " << *expr;
    }
      
    
    Skip::Skip () : Instruction (findInstrIndex<Skip> ()) {}
    std::ostream& Skip::output (std::ostream& os) const  {
      return os << "Skip";
    }
    
    Load::Load (Register_ptr dest,Expr_ptr addr) : Instruction (findInstrIndex<Load> ()),
						   assignee(dest),
						   address(addr) {}

    std::ostream& Load::output (std::ostream& os) const  {
      return os << *assignee <<" <- *" << *address;
    }
    
    Store::Store (Expr_ptr toStore, Expr_ptr address) : Instruction(findInstrIndex<Store> ()),
							storee(toStore),
							address (address) {}
    
    std::ostream& Store::output (std::ostream& os) const  {
      return os << "*" << *address <<" <- " << *storee;
    }
    
    
    
  }
}
