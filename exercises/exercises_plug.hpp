#ifndef _PLUG__
#define _PLUG__

#include "ir/cfa.hpp"
#include <cstdint>
#include <functional>
#include <vector>
#include <stdexcept>
#include <fmt/core.h>
#include <ostream>
#include <memory>


namespace FMTeach {

  class NotSolvedYet : public std::runtime_error {
  public:
    NotSolvedYet (const std::string& s) : std::runtime_error (fmt::format ("Exercise not solver. Go to  {} for adding your solution",s)) {}


    
  };

  class Result {
  public:
    virtual ~Result () {}
    virtual std::ostream& writeResult (std::ostream& ) = 0;
    
  };

  using Result_ptr = std::unique_ptr<Result>;
  
  struct Exercise {
    Exercise (const std::string& name);

    virtual Result_ptr teacher_solution (const FMTeach::IR::CFA&) = 0;
    virtual Result_ptr student_solution (const FMTeach::IR::CFA&) = 0;
    
    std::string name;
    
  };


  const std::vector<Exercise*>& exercies (); 
  
}


#endif
