

#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include <cstdint>
#include <ostream>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <functional>
#include <unordered_set>


template<class T>
concept HasHash =  requires (const T& t) {
  t.hash ();
};


namespace std {    
  template <HasHash H>
  struct hash<H> {
    auto operator() (const H&h)   {
      return h.hash ();
    }
  };
}

namespace FMTeach {

  namespace Exer4 {

    
    class OutOfRange : public std::runtime_error {
    public:
      OutOfRange () : runtime_error ("OutOfRange") {}
    };

    struct Hasher {
      template<class T>
      Hasher& operator<< (const T& val) {
	//stolen from boost
	std::hash<T> hasher;
	seed ^=  hasher(val) + 0x9e3779b9 + (seed<<6) + (seed>>2);
      }

      auto getHash () const {return seed;}
      
    private:
      std::size_t seed;
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

      auto hash () const {
	Hasher h;
	for (size_t i = 0; i < size; ++i) {
	  h << _internal.get()[i];
	}
	return h.getHash ();
      }
      
    private:
      std::unique_ptr<T[]> _internal;
      std::size_t size;
    };


    enum class InitStatus {
      Initialised,
      Uninitialised
    };
    
    class ExecutionState {
    public:
      ExecutionState (std::size_t regs, FMTeach::IR::Location_ptr loc) : registers(regs),loc(loc) {
	
      }
      
      ExecutionState (const ExecutionState& s) =default;
      ExecutionState (ExecutionState&&) = default;
      
      auto& getRegisters () {return registers;}
      
      auto& getRegisters () const {return registers;}
      

      auto& getLocation () {return loc;}
      void setLocation (FMTeach::IR::Location_ptr l) { loc = l;}
      
      auto hash () const {
	Hasher hash;
	hash << registers << loc;
	return hash.getHash ();
      }
      
    private:
      Buffer<InitStatus> registers;
      FMTeach::IR::Location_ptr loc;
    };
    
    class InitialisedExer : public FMTeach::Exercise  {
    public:
      InitialisedExer () : Exercise ("Interpreter") {}
      FMTeach::Result_ptr teacher_solution (const FMTeach::IR::CFA&) override;
      FMTeach::Result_ptr student_solution (const FMTeach::IR::CFA&) override;
      

    };

    class ResultExer : public FMTeach::Result  {
    public:
      ResultExer ()    {}
      std::ostream& writeResult ( std::ostream& os) override {
	os << "Nothing yet" << std::endl;
      }
    };
  }
} // namespace FMTeach

namespace std {
  template<>
  struct hash<FMTeach::Exer4::InitStatus> {
    auto operator () (const FMTeach::Exer4::InitStatus& s) const{
      return static_cast<int> (s);
    }
  };
  
}
    
