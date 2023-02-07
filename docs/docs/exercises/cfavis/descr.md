
## Exercise 2 
In this exercise we wish to obtain  a graphical overview of the structure of the CFA.  
Your solution should be integrated into `exercises/exer2/exer.cpp`

``` C++
#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include "setup.hpp"
#include <cstdint>

namespace FMTeach {
  namespace Exer2 {

    FMTeach::Result_ptr FMTeach::Exer2::CFAVisualiseExer::student_solution (const FMTeach::IR::CFA&)  {
      Graph g; // (1)
	  throw NotSolvedYet (__FILE__);    // (2)
	  return std::make_unique<FMTeach::Exer2::ResultExer> (std::move(g));
    }
  }

}

namespace {
  static FMTeach::Exer2::CFAVisualiseExer exer;
}

```

1. Graph structure you should add your solution to. You probably want to look at the file `exercises/exer2/setup.hpp` for the interface of the `Graph` class 
2. Replace this line with your solution


### Graph structure  
To avoid you have to acquaint yourself with Graphviz (or similar graphing library), we provide a very simplified  `Graph g`  interface  to Grapviz. 
In your code you can add an edge between `Location_ptr a` and `Location_ptr b` with label `std::string s` by calling `g.makeEdge (a,b,c)`.  



