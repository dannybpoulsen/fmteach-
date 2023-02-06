

#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include <cstdint>
#include <ostream>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <cassert>

namespace FMTeach {

  namespace Exer3 {

    class OutOfRange : public std::runtime_error {
    public:
      OutOfRange () : runtime_error ("OutOfRange") {}
    };
    
    template<class T>
    class Buffer {
    public:
      Buffer (std::size_t elementer) : _internal(new T[elementer]),size(elementer) {}
      Buffer (const Buffer& buf) : _internal(new T[buf.size]),size(buf.size) {
	std::copy (buf._internal.get(),buf._internal.get()+buf.size,_internal.get());
      }
      Buffer (Buffer&&) = default;

      auto operator[] (std::size_t e) const {
	if (e >= size) {
	  throw OutOfRange{};
	  
	}
	return _internal.get ()[e];
      }
      
      void set (std::size_t index,T s)  {
	if (index >= size) {
	  throw OutOfRange{};
	  
	}
	_internal.get ()[index] = s;
	assert(_internal.get ()[index] == s);
}

      std::ostream& output (std::ostream& os) {
	for (std::size_t i = 0; i < size; ++i) {
	  auto c = _internal.get()[i];
	  if (std::isprint (c)) {
	    os << c;
	  }
	  else
	    os << ".";
	}
	return os;
      }
      
    private:
      std::unique_ptr<T[]> _internal;
      std::size_t size;
    };
    
    class ExecutionState {
    public:
      ExecutionState (std::size_t regs, std::size_t memsize, FMTeach::IR::Location_ptr loc) : registers(regs),memory(memsize),loc(loc) {}
      ExecutionState (const ExecutionState& s) =default;
      ExecutionState (ExecutionState&&) = default;
      
      auto& getRegisters () {return registers;}
      auto& getMemory () {return memory;}

      auto& getRegisters () const {return registers;}
      auto& getMemory () const {return memory;}
      

      auto& getLocation () {return loc;}
      void setLocation (FMTeach::IR::Location_ptr l) { loc = l;}
      
      
    private:
      Buffer<std::int8_t> registers;
      Buffer<std::int8_t> memory;
      FMTeach::IR::Location_ptr loc;
    };

    class InterpreterExer : public FMTeach::Exercise  {
    public:
      InterpreterExer () : Exercise ("Interpreter") {}
      FMTeach::Result_ptr teacher_solution (const FMTeach::IR::CFA&) override;
      FMTeach::Result_ptr student_solution (const FMTeach::IR::CFA&) override;
      

    };

    class ResultExer : public FMTeach::Result  {
    public:
      ResultExer (ExecutionState&& state) :state(std::move(state))   {}
      std::ostream& writeResult ( std::ostream& os) override {
	return state.getMemory ().output (os) << std::endl;
      }
      private:
      ExecutionState state;
    };
  }
}
    
