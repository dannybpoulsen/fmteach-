#ifndef _WHILEY_COMPILER__
#define _WHILEY_COMPILER__

#include "whiley/ast.hpp"
#include "ir/cfa.hpp"

namespace FMTeach {
  namespace Whiley {
    class Compiler : private NodeVisitor {
    public:
      FMTeach::IR::CFA Compile (const FMTeach::Whiley::Program&);
      void visitIdentifier (const Identifier&) override ;
      void visitNumberExpression (const NumberExpression& ) override ; 
      void visitDerefExpression (const DerefExpression& ) override ;
      void visitBinaryExpression (const BinaryExpression& ) override ;  
      void visitAssignStatement (const AssignStatement& ) override ; 
      void visitNonDetAssignStatement (const NonDetAssignStatement& ) override ; 
      
      void visitIfStatement (const IfStatement& ) override ; 
      void visitSkipStatement (const SkipStatement& ) override ; 
      void visitWhileStatement (const WhileStatement& ) override ; 
      void visitSequenceStatement (const SequenceStatement& ) override ; 
      void visitMemAssignStatement (const MemAssignStatement&) override;
      
    private:
      struct Internal;
      Internal* _internal = nullptr;
    };
  }
}

#endif
