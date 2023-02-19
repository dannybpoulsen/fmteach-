#ifndef _EXECSTATE__
#define _EXECSTATE__

#include "ir/cfa.hpp"
#include "hash.hpp"
#include <cassert>
#include <iostream>

class OutOfRange : public std::runtime_error {
public:
  OutOfRange() : runtime_error("OutOfRange") {}
};

class NonDetNotSupported : public std::runtime_error {
public:
  NonDetNotSupported() : runtime_error("NonDetNotSupported") {}
};

template <class T>
class Buffer {
public:
  Buffer(std::size_t elementer) : _internal(new T[elementer]), size(elementer) {
    std::fill(_internal.get(), _internal.get() + size, T::defaultValue ());
  }

  Buffer(const Buffer &buf) : _internal(new T[buf.size]), size(buf.size) {
    std::copy(buf._internal.get(),
	      buf._internal.get() + buf.size,
              _internal.get());
  }
  Buffer(Buffer &&) = default;

  auto operator[](std::size_t e) const {
    if (e >= size) {
      throw OutOfRange{};
    }
    return _internal.get()[e];
  }

  void set(std::size_t index, T s) {
    if (index >= size) {
      throw OutOfRange{};
    }
    _internal.get()[index] = s;
  }
  
  std::ostream &output(std::ostream &os) const {
    for (std::size_t i = 0; i < size; ++i) {
      _internal.get()[i].output (os);
      
    }
    return os;
  }

  std::size_t hash () const  {
    FMTeach::Hash::HashCombine combiner;
    std::for_each (_internal.get(),_internal.get()+size,[&combiner](const T& t) {combiner << t;});
    return combiner;
  }
  
private:
  std::unique_ptr<T[]> _internal;
  std::size_t size;
};

template<typename T>
class Value {
public:
  Value (T v) : val(v) {}
  Value () : val(0) {}
  Value operator+ (const Value<T>& t) {return Value(val+t.val);}
  Value operator- (const Value<T>& t) {return Value(val-t.val);}
  Value operator* (const Value<T>& t) {return Value(val*t.val);}
  Value operator/ (const Value<T>& t) {return Value(val / t.val);}

  Value operator<= (const Value<T>& t) {return Value(val <= t.val);}
  Value operator< (const Value<T>& t) {return Value(val < t.val);}
  Value operator>= (const Value<T>& t) {return Value(val >= t.val);}
  Value operator> (const Value<T>& t) {return Value(val > t.val);}
  Value operator== (const Value<T>& t) {return Value(val == t.val);}
  Value operator!= (const Value<T>& t) {return Value(val != t.val);}
  Value operator! () {return Value(!val);}
  Value operator- () {return Value(-val);}
  operator T () {return val;}
  
  std::size_t hash () const {return val;}

  static Value defaultValue () {return 0;}
  
  std::ostream& output (std::ostream& os) const {
    if (std::isprint(val)) {
      return os << val;
    } else
      return os << ".";
    
  }
  private:
  T val;
};

template<class T>
class ExecState {
public:
  ExecState(std::size_t regs, std::size_t memsize,
                 FMTeach::IR::Location_ptr loc)
      : registers(regs), memory(memsize), loc(loc) {}
  ExecState(const ExecState &s) = default;
  ExecState(ExecState &&) = default;

  auto &getRegisters() { return registers; }
  auto &getMemory() { return memory; }

  auto &getRegisters() const { return registers; }
  auto &getMemory() const { return memory; }

  auto &getLocation() { return loc; }
  void setLocation(FMTeach::IR::Location_ptr l) { loc = l; }

  std::size_t hash () const {
    return FMTeach::Hash::HashCombine{} << registers << memory << *loc;
  }

  auto& output (std::ostream& os) const {
    os << "@";
    loc->output (os) << "\n";
    os << "Registers:\n"; 
    registers.output (os) << "\n";
    os << "Memory:\n";
    memory.output (os) << "\n";
    return os;
  }
  
private:
  Buffer<T> registers;
  Buffer<T> memory;
  FMTeach::IR::Location_ptr loc;
};

#endif
