#ifndef _EXECSTATE__
#define _EXECSTATE__

#include "ir/cfa.hpp"
#include <cassert>

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
    std::fill(_internal.get(), _internal.get() + size, T{0});
  }

  Buffer(const Buffer &buf) : _internal(new T[buf.size]), size(buf.size) {
    std::copy(buf._internal.get(), buf._internal.get() + buf.size,
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
    assert(_internal.get()[index] == s);
  }

  std::ostream &output(std::ostream &os) {
    for (std::size_t i = 0; i < size; ++i) {
      auto c = _internal.get()[i];
      if (std::isprint(c)) {
        os << c;
      } else
        os << ".";
    }
    return os;
  }

private:
  std::unique_ptr<T[]> _internal;
  std::size_t size;
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

private:
  Buffer<T> registers;
  Buffer<T> memory;
  FMTeach::IR::Location_ptr loc;
};

#endif
