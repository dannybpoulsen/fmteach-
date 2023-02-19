#ifndef _IR__CFA__
#define _IR__CFA__

#include "ir/instructions.hpp"

#include <vector>

namespace FMTeach {
  namespace IR {
    class Location;
    using Location_ptr = std::shared_ptr<Location>;
    class Edge {
    public:
      Edge (Instruction_ptr&& instr, Location_ptr to) : to(to),instruction(std::move(instr)) {}
      
      auto& getInstruction () const {return instruction;};
      auto& getTo () const {return to;}
      
    private:
      Location_ptr to;
      Instruction_ptr instruction;
    };
    
    
    class Location {
    public:
      Location (std::string name, bool asser = false) : name(std::move(name)),assert(asser) {}
      auto& getName () const {return name;}
      void addEdge (Instruction_ptr&& instr, Location_ptr to) {
	_edges.emplace_back (std::move(instr),to);
      }

      auto& edges () const {return _edges;}
      auto isAssert () const {return assert;}
      std::size_t hash () const {return reinterpret_cast<std::size_t> (this);}
      std::ostream& output ( std::ostream& os) {
	return os << name  << ((assert ) ? ":-("  :   ":-)");
      }
    private:
      std::string name;
      std::vector<Edge> _edges;
      bool assert;
    };

    class CFA {
    public:
      CFA ()  {}

      auto makeLocation (std::string name, bool isInitial, bool assert = false) {
	locations.emplace_back (std::make_shared<Location> (name,assert));
	if (isInitial)
	  initial = locations.back ();
	return locations.back ();
      }

      auto makeRegister (std::string name) {
	registers.emplace_back (std::make_shared<Register> (registers.size(),name));
	return registers.back ();
      }

      auto getInitial ()const  {
	return initial;
      }

      auto& getRegisters () const {return registers;}
      
    private:
      std::vector<Location_ptr> locations;
      std::vector<Register_ptr> registers;
      Location_ptr initial{nullptr};
    };
    
    
  }
}
  
 

#endif
