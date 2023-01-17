#ifndef _PLUG__
#define _PLUG__

#include "ir/cfa.hpp"
#include <cstdint>
#include <functional>
#include <vector>
#include <stdexcept>
#include <fmt/core.h>


namespace FMTeach {

  class NotSolvedYet : public std::runtime_error {
  public:
    NotSolvedYet (const std::string& s) : std::runtime_error (fmt::format ("Exercise not solver. See {} for the exercise description and adding your solution",s)) {}


    
  };
  
  using solv_func = std::function<std::int64_t(const FMTeach::IR::CFA&)>;
  struct Exercise {
    Exercise (const std::string& name, solv_func teacher, solv_func student);
    solv_func teacher_solution;
    solv_func student_solution;
    std::string name;
    
  };


  const std::vector<Exercise*>& exercies (); 
  
}


#endif
