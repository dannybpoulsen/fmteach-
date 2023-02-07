# Exercise 1 

In this exercise we want to count the number of location in a CFA. You should implement your solution in the file `exercises/exer1/exer.cpp`.
This is not particularly useful in general, but this task enables you to explore the repository. 

``` C++
#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include "setup.hpp"
#include <cstdint>

namespace FMTeach {
  namespace Exer1 {

    FMTeach::Result_ptr FMTeach::Exer1::EnumStatesExer::student_solution (const FMTeach::IR::CFA& /* (2) */ )  {
      throw NotSolvedYet (__FILE__);    // (3)
      return std::make_unique<FMTeach::Exer1::ResultExer> (0); // (1)
    }
  }

}

namespace {
  static FMTeach::Exer1::EnumStatesExer exer;
}

```

1. :man_raising_hand: You should change `0` to the number of locations your implmenentation found.
2. :man_raising_hand: Probably have a look at `libs/ir/include/cfa.hpp" for the interface of the CFA class.
3. :man_raising_hand: Replace this `throw` with your solution 


## Tips  

=== "General Idea"  
    Intuitively what you need is only to run through all locations and increment a counter everytime you encounter an unexplored one.   

=== "Sets in C++"  
    C++ have a type-parameterised implementation of sets in the class  [`std::unordered_set`](https://cplusplus.com/reference/unordered_set/unordered_set/). You can use to keep all visited CFA-locations. Below are some examples of using the class.  

    ``` C++
    #include <unordered_set> //(4)
    
    FMTeach::Result_ptr FMTeach::Exer1::EnumStatesExer::student_solution (const FMTeach::IR::CFA& cfa  )  {
  	std::unordered_set<MiniMC::IR::Location_ptr> passed; // (1)
	passed.insert (cfa.getInitial ()); // (2)
	if (passed.count (cfa.getInitial ()) ; // (3) 
		
	}
    ```

    1. Define a `std::unordered_set` storing `Location_ptr`  
    2. Insert initial location of `cfa` into `passed`  
    3. Check if the initial location is already  in `passed`  
    4. Include header wit hthe definition of `std::unordered_set`  

=== "vector in C++"
	You can use the type-parameterised [`vector`](https://cplusplus.com/reference/vector/vector/) -class of c++ as a waiting list.  
    ``` C++
    #include <uvector> //(4)
    
    FMTeach::Result_ptr FMTeach::Exer1::EnumStatesExer::student_solution (const FMTeach::IR::CFA& cfa  )  {
  	std::vector<MiniMC::IR::Location_ptr> waiting; // (1)
	waiting.push_back (cfa.getInitial ()); // (2)
	if (waiting.size () ; // (3) 
	
	auto next = waiting.back (); // (5)
	waiting-pop_back (); // (6)
	
	}
    ```  
    
	1. Define a `vector` storing `Location_ptr`  
    2. Insert initial location of `cfa` into `waiting`  
    3. Check if there is something in `waiting`  
    4. Include header wit the definition of `std::vector`  
	5. Get the last element of `waiting` 
	6. Remove the last element from `waiting`
