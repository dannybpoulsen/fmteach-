
#include "ir/instructions.hpp"

#include <vector>

namespace FMTeach {
  namespace IR {
    class Location;
    using Location_ptr = std::shared_ptr<Location>;
    class Edge {
    public:
      Edge (Instruction_ptr&& instr, Location_ptr to) : to(to),instruction(std::move(instr)) {}
      
      auto& getInstruction () const {return instruction};
      auto& getTo () const {return to;}
      
    private:
      Location_ptr to;
      Instruction_ptr instruction;
    }:
    

    class Location {
      Location (std::string name) : name(std::move(name)) {}
      auto& getName () const {return name;}
      void addEdge (Instruction_ptr&& ptr, Location_ptr to) {
	edges.emplace_back (std::move(instr),to);
      }

      auto& edges () const {return edges;}
      
      
    private:
      std::string name;
      std::vector<Edge> edges;
    };

    class CFA {
    public:
      CFA ()  {}

      auto makeLocation (std::string name, bool initial) {
	locations.emplace_back (std::make_shared<Location> (name));
	if (initial)
	  initial = locations.back ();
	return locations.back ();
      }

      auto makeRegister (std::string name) {
	registers.emplace_back (std::make_shared<Register> (registeds.size(),name));
	return registers.back ();
      }

      auto getInitial () {
	return initial;
      }
      
    private:
      std::vector<Location_ptr> locations;
      std::vector<Register_ptr> registers;
      Location_ptr initial{nullptr};
    };
    
    
  }
}
  
 
