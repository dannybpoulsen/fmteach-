#ifndef _HASH__
#define _HASH__

#include <functional>

template<class T>
concept HasHash =  requires (const T& t) {
  t.hash ();
};


namespace std {    
      template <HasHash H>
      struct hash<H> {
	auto operator() (const H&h) const   {
	  return h.hash ();
	}
      };
    }


namespace FMTeach {
  namespace Hash {
    

    class HashCombine {
    public:
      HashCombine (std::size_t seed = 0) : seed(seed) {}

      template<class Obj>
      auto& operator<< (const Obj& obj) const {
	
	seed ^= std::hash<Obj>{}(obj) + 0x9e3779b9 + (seed<<6) + (seed>>2);
	return *this;
      }

      auto get () const {return seed;}
      operator std::size_t () const {return get();} 
      
    private:
      mutable std::size_t seed; 
    };
    
  }
}

#endif
