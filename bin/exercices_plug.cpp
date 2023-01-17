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

  
  Exercise::Exercise (const std::string& name, solv_func teacher, solv_func student) : teacher_solution(teacher),student_solution (student),name(name) {
    registerExercise (this);
  }
  
}
