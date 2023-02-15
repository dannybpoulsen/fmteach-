#ifndef _WHILEY_AST__
#define _WHILEY_AST__


#include <string>
#include <memory>
#include <vector>
#include <unordered_set>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cstdint>

namespace FMTeach {
  namespace Whiley {
    class Identifier;
    class NumberExpression;
    class BinaryExpression;
    class DerefExpression;
    class AssignStatement;
    class NonDetAssignStatement;
    class MemAssignStatement;
    class DeclareStatement;
    class IfStatement;
    class WhileStatement;
    class SequenceStatement;
    class SkipStatement;
    
    
    class NodeVisitor {
    public:
      virtual ~NodeVisitor () {}
      virtual void visitIdentifier (const Identifier&) = 0;
      virtual void visitNumberExpression (const NumberExpression& ) = 0;
      virtual void visitBinaryExpression (const BinaryExpression& ) = 0;
      virtual void visitDerefExpression (const DerefExpression& ) = 0;
      
      virtual void visitAssignStatement (const AssignStatement& ) = 0;
      virtual void visitNonDetAssignStatement (const NonDetAssignStatement& ) = 0;
      virtual void visitMemAssignStatement (const MemAssignStatement& ) = 0;
      
      virtual void visitIfStatement (const IfStatement& ) = 0;
      virtual void visitSkipStatement (const SkipStatement& ) = 0;
      
      virtual void visitWhileStatement (const WhileStatement& ) = 0;
      virtual void visitSequenceStatement (const SequenceStatement& ) = 0;
      
    };

    struct fileloc_t {
      std::size_t line{1};
      std::size_t col{1};
      
    };

    inline std::ostream& operator<< (std::ostream& os, const fileloc_t& loc) {
      return os << loc.line <<":"<<loc.col;
    }
    
    struct location_t {
      fileloc_t begin;
      fileloc_t end;

      void step () {begin = end; end = fileloc_t{};}
      void movecol (std::size_t s) {end.col+=s;}
      void newline () {
	end.line++;
	end.col = 1;
	begin = end;
      }
    };

    inline std::ostream& operator<< (std::ostream& os, const location_t& loc) {
      return os << loc.begin << " - " << loc.end;
    }
    
    
    class Node {
    public:
      Node (const location_t& loc = location_t{}) : location (loc) {}
      virtual ~Node () {}
      virtual void accept (NodeVisitor&) const = 0;
    private:
      location_t location;
    };

    std::ostream& operator<< (std::ostream&, const Node& );
    
    using Node_ptr = std::unique_ptr<Node>;
    
    class Expression : public Node {
    public:
      Expression (const location_t& loc) : Node(loc) {}
      virtual ~Expression () {}
      virtual bool isConstant () const = 0;
      
    };
    
    using Expression_ptr = std::unique_ptr<Expression>;
    
    
    class Identifier : public Expression {
    public:
      Identifier (std::string name, const location_t& loc = location_t{}) : Expression(loc), name(std::move(name)) {}
      auto getName () const {return name;}
      void accept (NodeVisitor& v) const {v.visitIdentifier (*this);} 
      bool isConstant () const override {return false;}
      
    private:
      std::string name;
    };

    class NumberExpression : public Expression {
    public:
      NumberExpression (std::int8_t value, const location_t& loc) : Expression(loc),value(value) {}
      auto getValue () const {return value;}
      void accept (NodeVisitor& v) const {v.visitNumberExpression (*this);}
      bool isConstant () const override {return true;}
      
    private:
      std::int8_t value;
    };
    
    enum class BinOps {
      Add,
      Sub,
      Div,
      Mul,
      LEq,
      GEq,
      Lt,
      Gt,
      Eq,
      NEq
    };

    class BinaryExpression : public Expression {
    public:
      BinaryExpression (Expression_ptr&& l, Expression_ptr&& r, BinOps op, const location_t& loc) : Expression(loc),
												    left(std::move(l)),
												    right(std::move(r)),
												    type(op) {}
      auto getOp () const {return type;}
      auto& getLeft () const {return *left;}
      auto& getRight () const {return *right;}
      bool isConstant () const override {return false;}
      void accept (NodeVisitor& v) const {v.visitBinaryExpression (*this);}
      
    private:
      Expression_ptr left;
      Expression_ptr right;
      BinOps type;
    };

    class DerefExpression : public Expression {
    public:
      DerefExpression (Expression_ptr&& l, const location_t& loc) : Expression(loc),
								    left(std::move(l)) {}
								   
      auto& getMem () const {return *left;}
      bool isConstant () const override {return false;}
      void accept (NodeVisitor& v) const {v.visitDerefExpression (*this);}
      
    private:
      Expression_ptr left;
    };

    class Statement : public Node {
    public:
      Statement (const location_t& loc) : Node(loc) {}
      virtual ~Statement () {}
    };

    using Statement_ptr = std::unique_ptr<Statement>;

    class SkipStatement  : public Statement{
    public:
      SkipStatement (const location_t& loc) : Statement(loc) {}
      void accept (NodeVisitor& v) const {v.visitSkipStatement (*this);}
    };
    
    class AssignStatement  : public Statement{
    public:
      AssignStatement (std::string assignName, Expression_ptr&& expr, const location_t& loc) : Statement(loc),
											       assignName(std::move(assignName)),
											       expr(std::move(expr)) {}
      
      void accept (NodeVisitor& v) const override {v.visitAssignStatement(*this);}
      auto& getAssignName () const {return assignName;}
      auto& getExpression () const {return *expr;}
      
      private:
      Expression_ptr expr;
      std::string assignName;
    };

     class NonDetAssignStatement  : public Statement{
    public:
       NonDetAssignStatement (std::string assignName, const location_t& loc) : Statement(loc),
									       assignName(std::move(assignName)) {}
      
      void accept (NodeVisitor& v) const override {v.visitNonDetAssignStatement(*this);}
      auto& getAssignName () const {return assignName;}
      
     private:
      std::string assignName;
    };
    
    class MemAssignStatement  : public Statement{
    public:
      MemAssignStatement (Expression_ptr&& mem, Expression_ptr&& expr, const location_t& loc) : Statement(loc),
												memLoc(std::move(mem)),
												expr(std::move(expr)) {}
      
      void accept (NodeVisitor& v) const override {v.visitMemAssignStatement(*this);}
      auto& getMemLoc () const {return *memLoc;}
      auto& getExpression () const {return *expr;}
      
      private:
      Expression_ptr expr;
      Expression_ptr memLoc;
    };
    
    class IfStatement  : public Statement{
    public:
      IfStatement (Expression_ptr&& cond,Statement_ptr ifb, Statement_ptr elseb, const location_t& loc) : Statement(loc),
													  cond(std::move(cond)) ,
													  if_body(std::move(ifb)),
													  else_body(std::move(elseb)) {}
      
      void accept (NodeVisitor& v) const override {v.visitIfStatement(*this);}
      auto& getCondition () const {return *cond;}
      auto& getIfBody () const {return *if_body;}
      auto& getElseBody () const {return *else_body;}
      
    private:
      Expression_ptr cond;
      Statement_ptr if_body;
      Statement_ptr else_body;
      
    };

    class WhileStatement  : public Statement{
    public:
      WhileStatement (Expression_ptr&& cond,Statement_ptr body, const location_t& loc) : Statement(loc),
											 cond(std::move(cond)) ,
											 body(std::move(body)) {}
      
      void accept (NodeVisitor& v) const override {
	v.visitWhileStatement (*this);
      }

      auto& getCondition () const {return *cond;}
      auto& getBody () const {return *body;}
      
    private:
      Expression_ptr cond;
      Statement_ptr body;
      
    };

    class SequenceStatement  : public Statement{
    public:
      SequenceStatement (Statement_ptr first,Statement_ptr second, const location_t& loc) : Statement(loc),
											    first(std::move(first)) ,
											    second(std::move(second)) {}
      
      void accept (NodeVisitor& v) const {
	v.visitSequenceStatement (*this);
      }

      auto& getFirst () const {return *first;}
      auto& getSecond () const {return *second;}
      
    private:

      Statement_ptr first;
      Statement_ptr second;
      
    };


    template<class T>
    class Stack {
    public:
      auto size () const {return stack.size();}
      void insert (T&& t) { stack.push_back(std::move(t));}
      auto pop () {
	if (stack.size ()) {
	  auto r = std::move(stack.back ());
	  stack.pop_back ();
	  return r;
	}
	throw std::runtime_error ("Missing element on stack");	
      
      }
    private:
      std::vector<T> stack;
    };

    class Program {
    public:
      Program (std::unordered_set<std::string>&& vars, Statement_ptr&& stmt) : variableNames(std::move(vars)),
									      stmt(std::move(stmt)) {}

      auto& getStmt () const {return *stmt;}
      auto& getVars () const {return variableNames;}
											     
	       
    private:
      std::unordered_set<std::string> variableNames;
      Statement_ptr stmt;
    };

    inline std::ostream& operator<< (std::ostream& os, const Program& prgm) {
      std::for_each (prgm.getVars().begin(),prgm.getVars().end(),[&os](auto& s){
	os << "var " << s << ";\n";
      });
      return os << prgm.getStmt ();
    }
    
    class ASTBuilder {
    public:
      
      
      void NumberExpr (std::int8_t val, const location_t& l) {
	exprStack.insert (std::make_unique<NumberExpression> (val,l));
      }

      void IdentifierExpr (const std::string name, const location_t& l) {
	exprStack.insert (std::make_unique<Identifier> (name,l));
      }

      void DerefExpr ( const location_t& l) {
	auto left = exprStack.pop ();  
	exprStack.insert (std::make_unique<DerefExpression> (std::move(left),l));
      }

      
      void BinaryExpr (BinOps op, const location_t& l) {
	auto right = exprStack.pop ();
	auto left = exprStack.pop ();  
	exprStack.insert (std::make_unique<BinaryExpression> (std::move(left),std::move(right),op,l));
      }

      void AssignStmt (std::string name, const location_t& l) {
	if (vars.count (name)) {
	 
	  auto expr = exprStack.pop ();
	  
	  stmtStack.insert (std::make_unique<AssignStatement> (name,std::move(expr),l));
	}
	else {
	  throw std::runtime_error ("Variable does not exist");

	}
      }
      
      void DeclareStmt (std::string name, const location_t& l) {
	if (!vars.count (name)) {
	  vars.insert (name);
	}
	else 
	  throw std::runtime_error ("Variable already defined");
      }
      
      
      void IfStmt (const location_t& l)  {
	auto expr = exprStack.pop ();
	auto elseb = stmtStack.pop ();
	auto ifb = stmtStack.pop ();
	
	stmtStack.insert (std::make_unique<IfStatement> (std::move(expr),
							 std::move(ifb),
							 std::move(elseb),
							 l)
			  );
      }

       void SkipStmt (const location_t& l) {
	
	 stmtStack.insert (std::make_unique<SkipStatement> (l));
      }

      void MemAssignStmt (const location_t& l) {
	auto assign_val = exprStack.pop ();
	auto mem = exprStack.pop ();
	
	stmtStack.insert (std::make_unique<MemAssignStatement> (std::move(mem),
								std::move(assign_val),
								l)
			  );
      }
      
      
      void WhileStmt (const location_t& l) {
	auto expr = exprStack.pop ();
	auto body = stmtStack.pop ();
	
	stmtStack.insert (std::make_unique<WhileStatement> (std::move(expr),
							    std::move(body),
							    l
							    )
			  
			  );
	
        }

      void SequenceStmt ( const location_t& l) {
	auto second = stmtStack.pop ();
	auto first = stmtStack.pop ();
	
	stmtStack.insert (std::make_unique<SequenceStatement> (std::move(first),
							       std::move(second),
							       l)
			  );
	
        }
      
      auto get () {
	return Program (std::move(vars),stmtStack.pop ());
      }
	
      
    private:
      Stack<Expression_ptr> exprStack;
      Stack<Statement_ptr> stmtStack;
      std::unordered_set<std::string> vars;
      
      
    };
    
    
  }
  
}


#endif
