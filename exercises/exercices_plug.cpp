#include "exercises_plug.hpp"
#include <vector>

namespace FMTeach {

  auto& getExer () {
    static std::vector<Exercise*> exer;
    return exer;
  }
  
  void registerExercise (Exercise* exer) {
    getExer ().push_back (exer);
  }
  
  const std::vector<Exercise*>& exercies () {
    return getExer ();
  }

  
  Exercise::Exercise (const std::string& name) : name(name) {
    registerExercise (this);
  }
  
}
