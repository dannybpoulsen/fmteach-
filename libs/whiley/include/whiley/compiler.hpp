#ifndef _WHILEY_COMPILER__
#define _WHILEY_COMPILER__

#include "whiley/ast.hpp"
#include "ir/cfa.hpp"

namespace FMTeach {
  namespace Whiley {
    class Compiler : private NodeVisitor {
    public:
      FMTeach::IR::CFA Compile (const FMTeach::Whiley::Program&);
      void visitIdentifier (const Identifier&);
      void visitNumberExpression (const NumberExpression& ); 
      void visitBinaryExpression (const BinaryExpression& ); 
      void visitAssignStatement (const AssignStatement& ); 
      void visitIfStatement (const IfStatement& ); 
      void visitSkipStatement (const SkipStatement& ); 
      void visitWhileStatement (const WhileStatement& ); 
      void visitSequenceStatement (const SequenceStatement& ); 
      
    private:
      struct Internal;
      Internal* _internal = nullptr;
    };
  }
}

#endif
