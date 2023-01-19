#include "exercises_plug.hpp"
#include "whiley/parser.hpp"
#include "whiley/compiler.hpp"
#include "ir/cfa.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <sstream>

namespace po = boost::program_options;

int main (int argc, char** argv) {
  bool runSolution = false;
  std::string inputfile = "";
  std::string selexer = "";

  po::options_description options("FMTeach");
  std::unordered_map<std::string,FMTeach::Exercise*> exercises;
  std::stringstream str;
  
  str << "Select exercise:\n"; 
  for (auto& e : FMTeach::exercies ()) {
    str << "\t" << e->name<< "\n";  
    exercises.emplace (e->name,e);
  }
  
  
  
  options.add_options()
    ("i,inputfile", po::value<std::string>(&inputfile), "Whiley program")
    ("s,solution", po::bool_switch(&runSolution),"Run the solution")
    ("e,exercises", po::value<std::string> (&selexer),str.str ().c_str());


  try {
    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(argc, argv)
      .options(options)
      .run();
    
      po::store(parsed, vm);
      po::notify(vm);
      
      
  }
  catch (po::error& e) {
    std::cerr << e.what () << std::endl;
    return false;
  }
  

  if (!exercises.count (selexer)) {
    std::cerr << options << std::endl;
    return -1;
  }
  
  if (inputfile.size ()) {
    auto exer = exercises.at (selexer);
    FMTeach::Whiley::WParser parser;
    auto prgm = parser.parse (inputfile);
    auto cfa = FMTeach::Whiley::Compiler{}.Compile ( prgm);

    FMTeach::Result_ptr result;
    try {
      if (runSolution) 
	result = exer->teacher_solution (cfa);
      else
	result = exer->student_solution (cfa);
      
      result->writeResult (std::cout);
      
    }catch (FMTeach::NotSolvedYet& e) {
      std::cerr << e.what () << std::endl;
    }
  }
}
