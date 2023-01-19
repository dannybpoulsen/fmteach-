

#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include <cstdint>
#include <ostream>
#include <memory>

namespace FMTeach {

  namespace Exer2 {

    struct Node;
    class Graph {
    public:
      Graph ();
      Graph (const Graph&) = delete;
      Graph (Graph&& g); 
      ~Graph ();
      void makeEdge (FMTeach::IR::Location_ptr f,FMTeach::IR::Location_ptr t, const std::string& );
      std::ostream& output (std::ostream&);
      
    private:
      struct Internal;
      std::unique_ptr<Internal> _internal;
    };
     
    
    

    class CFAVisualiseExer : public FMTeach::Exercise  {
    public:
      CFAVisualiseExer () : Exercise ("CFAVis") {}
      FMTeach::Result_ptr teacher_solution (const FMTeach::IR::CFA&) override;
      FMTeach::Result_ptr student_solution (const FMTeach::IR::CFA&) override;
      

    };

    class ResultExer : public FMTeach::Result  {
    public:
      ResultExer (Graph&& g)  : graph(std::move(g)) {}
      std::ostream& writeResult ( std::ostream& os) override {
	return graph.output (os);
      }
      
            
    private:
      Graph graph;
    };
  }
}
    
