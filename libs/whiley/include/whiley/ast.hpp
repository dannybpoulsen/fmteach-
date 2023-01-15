
#include <string>
#include <memory>

namespace FMTeach {
  namespace Whiley {
    class NodeVisitor;
    class Node {
    public:
      virtual ~Node () {}
      virtual void accept (NodeVisitor&) = 0;
    };

    using Node_ptr = std::unique_ptr<Node>;
    
    class Expression {
    public:
      virtual ~Expression () {}
      virtual bool isConstant () const {return false;}
    
    };
    
    using Expression_ptr = std::unique_ptr<Expression>;
    
    
    class Identifier : Expression {
    public:
      Identifier (std::string name) : name(std::move(name)) {}
      auto getName () const {return name;}
      void accept (NodeVisitor&) const {} 
    private:
      std::string name;
    };

    class Number : Expression {
    public:
      Number (std::int8_t value) : value(value) {}
      auto getValue () const {return value;}
      void accept (NodeVisitor&) const {}
    private:
      std::int8_t value;
    };
    
    enum class BinOps {
      Plus,
      Minus,
      Div,
      Mul,
      LEq,
      GEq,
      Lt,
      Gt,
      Eq,
      NEq
    };

    class BinaryExpression {
    public:
      BinaryExpression (Expression_ptr&& l, Expression_ptr&& r, BinOps op) : left(std::move(l)),
									     right(std::move(r)),
									     type(op) {}
      auto getOp () const {return type;}
      auto& getLeft () const {return *left;}
      auto& getRight () const {return *right;}
      
    private:
      Expression_ptr left;
      Expression_ptr right;
      BinOps type;
    };
    
  }
}
