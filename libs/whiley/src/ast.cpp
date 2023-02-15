#include "whiley/ast.hpp"

namespace FMTeach {
  namespace Whiley {

    class OutputVisitor : private NodeVisitor {
    public:
      OutputVisitor (std::ostream& o) : os(o) {}
      void visitIdentifier (const Identifier& ident) override {
	os << ident.getName ();
      }
      void visitNumberExpression (const NumberExpression& number) override {
	os << static_cast<int> (number.getValue ());
		
      }

      void visitDerefExpression (const DerefExpression& expr) override {
	os << "*";
	expr.getMem ().accept (*this);
	
		
      }
      
      
      void visitBinaryExpression (const BinaryExpression& binary) override {
	os << "(";
	binary.getLeft ().accept(*this);
	switch (binary.getOp ()) {
	case BinOps::Add:
	  os << " + ";
	  break;
	case BinOps::Sub:
	  os << " - ";
	  break;
	case BinOps::Mul:
	  os << " * ";
	  break;
	case BinOps::Div:
	  os << "/ ";
	  break;
	case BinOps::LEq:
	  os << "  <= ";
	  break;
	case BinOps::GEq:
	  os << "  >= ";
	  break;
	case BinOps::Lt:
	  os << "  < ";
	  break;
	case BinOps::Gt:
	  os << "  > ";
	  break;
	case BinOps::Eq:
	  os << " == ";
	  break;
	case BinOps::NEq:
	  os << "  != ";
	  break;
	}
	binary.getRight ().accept (*this);
      }
      void visitAssignStatement (const AssignStatement& ass) override {
	os << ass.getAssignName () << " = ";
	ass.getExpression ().accept (*this);
	os << ";\n";
      }

      void visitNonDetAssignStatement (const NonDetAssignStatement& ass) override {
	os << ass.getAssignName () << " = NonDet";
      }

      virtual void visitMemAssignStatement (const MemAssignStatement& assign) {
	os << "*";
	assign.getMemLoc ().accept (*this);
	os << " = ";
	assign.getExpression ().accept (*this);
      }
      
      
      void visitIfStatement (const IfStatement& ifs) override {
	os << "if (";
	ifs.getCondition ().accept(*this);
	os <<" ) {\n";
	ifs.getIfBody ().accept(*this);
	os << "\n}\n{";
	ifs.getElseBody ().accept (*this);
	os << "}\n";
      }
      void visitSkipStatement (const SkipStatement& ) override {
	os << "Skip";
      }
      
      void visitWhileStatement (const WhileStatement& whiles) override {
	os << "while (";
	whiles.getCondition ().accept(*this);
	os <<" ) {\n";
	whiles.getBody ().accept(*this);
	os << "\n}";
      }
      void visitSequenceStatement (const SequenceStatement& seg) override {
	seg.getFirst ().accept(*this);
	seg.getSecond ().accept(*this);
	
      }
      
      auto& operator() (const Node& n) {
	n.accept (*this);
	return os;
      }
      
    private:
      std::ostream& os;
    };
    
    std::ostream& operator<< (std::ostream& os, const Node& n)  {
      return OutputVisitor{os} (n);
      
    };
    

  }
}
