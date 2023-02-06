#include "ir/cfa.hpp"
#include "exercises_plug.hpp"
#include "setup.hpp"
#include <cstdint>
#include <ostream>
#include <graphviz/cgraph.h>

namespace FMTeach {

  namespace Exer2 {
    struct Graph::Internal {
      Internal () {
	graph = agopen(const_cast<char*> ("G"), Agdirected, NULL);
	agattr(graph,AGEDGE,const_cast<char*>("label"),const_cast<char*> (""));
      }
      ~Internal () {agclose (graph);}
      Agraph_t* graph;
      std::unordered_map<FMTeach::IR::Location_ptr,Agnode_t*> nodes;
    };

    Graph::~Graph () {}
    Graph::Graph () : _internal(std::make_unique<Internal> ()) {}
    Graph::Graph (Graph&&) = default;
    void Graph::makeEdge (FMTeach::IR::Location_ptr f,FMTeach::IR::Location_ptr t, const std::string& label) {
      static std::size_t i = 0;
      auto lookupOrCreate = [this](auto& loc) {
	if (!_internal->nodes.count (loc)) {
	  _internal->nodes.emplace(loc,agnode (_internal->graph,nullptr,true));
	}
	return _internal->nodes.at (loc);
      };

      auto from = lookupOrCreate (f);
      auto to = lookupOrCreate (t);
      auto e = agedge (_internal->graph,from,to,const_cast<char*> (std::to_string (++i).c_str ()),true);
      agset (e,const_cast<char*> ("label"),const_cast<char*> (label.c_str()));
    }

    std::ostream& Graph::output (std::ostream& os) {
      char* buf;
      size_t len;
      auto out = open_memstream(&buf,&len);
      agwrite (_internal->graph,out);
      os << buf;
      fclose (out);
      free (buf);
      return os;
    }
      
    
  }
}
