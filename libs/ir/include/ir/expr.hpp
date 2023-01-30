#ifndef _IR_EPXR__
#define _IR_EPXR__

#include <ostream>
#include <memory>
#include <cstdlib>
#include <string>

namespace FMTeach {
  namespace IR {

    //We only have signed integers
    // BinOp
    // Add
    // Sub
    // Div
    // Mul
    // LEq
    // GEq
    // Eq
    // NEq
    // Lt
    // Gt
    
    using exprtype_t = std::size_t;
    
    class Expr {
    public:
      
      virtual ~Expr () {}
      virtual std::ostream& output(std::ostream&) const = 0;
      exprtype_t exprType () const {return exprid;}
    protected:
      Expr (exprtype_t val) : exprid(val) {}
    private:
      exprtype_t exprid; 
    };

    inline std::ostream& operator<< (std::ostream& os, const Expr& e) {
      return e.output (os);
    }
    
    using Expr_ptr = std::shared_ptr<Expr>;
    
    enum class BinOp {
      Add,
      Sub,
      Div,
      Mul,
      LEq,
      GEq,
      Eq,
      NEq,
      Lt,
      Gt
    };

    
    class Constant : public Expr {
    public:
      Constant (std::int8_t val);
      std::ostream& output(std::ostream& os) const override {
	return os << static_cast<std::int64_t> (value);
      }
      
      auto getValue () const {return value;}
      
    private:
      std::int8_t value;
    };

    class Register : public Expr {
    public:
      Register (std::size_t number, std::string name = ""); 
      std::ostream& output(std::ostream& os) const override {
	if (name.size ())
	  return os << name;
	else
	  return os << "%r" << registernumber;

      }

      auto getNumber () const {return registernumber;}
      
    private:
      std::size_t registernumber;
      std::string name;
    };

    using Register_ptr = std::shared_ptr<Register>;
    
    template<BinOp b>
    class Binary : public Expr {
    public:
      
      Binary (Expr_ptr&& l, Expr_ptr&& r);
      std::ostream& output(std::ostream& os) const override {
	os << " ( ";
	left -> output (os);
	if constexpr (b == BinOp::Add) {
	  os << " + ";
	}
	else if constexpr (b == BinOp::Sub) {
	   os << " - ";
	}
	else if constexpr (b == BinOp::Div) {
	  os << " / ";
	}

	else if constexpr (b == BinOp::Mul) {
	   os << " * ";
	}

	else if constexpr (b == BinOp::LEq) {
	   os << " <= ";
	}

	else if constexpr (b == BinOp::GEq) {
	   os << " >= ";
	}

	else if constexpr (b == BinOp::Eq) {
	   os << " == ";
	}

	else if constexpr (b == BinOp::NEq) {
	   os << " != ";
	}

	else if constexpr (b == BinOp::Lt) {
	   os << " < ";
	}

	else if constexpr (b == BinOp::Gt) {
	   os << " > ";
	}
	right->output (os);
	return os << " ) ";
      }

      auto& getLeft () const {return *left;}
      auto& getRight () const {return *right;}
      
      
    private:
      Expr_ptr left;
      Expr_ptr right;
    };

    
    using AddExpr = Binary<BinOp::Add>;
    using SubExpr = Binary<BinOp::Sub>;
    using DivExpr = Binary<BinOp::Div>;
    using MulExpr = Binary<BinOp::Mul>;
    using LEqExpr = Binary<BinOp::LEq>;
    using GEqExpr = Binary<BinOp::GEq>;
    using EqExpr = Binary<BinOp::Eq>;
    using NEqExpr = Binary<BinOp::NEq>;
    using LtExpr = Binary<BinOp::Lt>;
    using GtExpr = Binary<BinOp::Gt>;
    

    
    enum class UnaryOp {
      Negation,
      UnMinus,
      Deref
    };
    
    template<UnaryOp b>
    class Unary : public Expr {
    public:
      
      Unary (Expr_ptr r);
      std::ostream& output(std::ostream& os) const override {
	if constexpr (b == UnaryOp::Negation) {
	  os << " ! ";
	}
	else if constexpr (b == UnaryOp::UnMinus) {
	  os << " - ";
	}
	else if constexpr (b == UnaryOp::Deref) {
	  os << " * ";
	}
	os << " ( ";
	right -> output (os);
	return os << " ) ";
      }

      auto& getInner () const {return *right;}
      
    private:
      Expr_ptr right;
    };

    using NegationExpr = Unary<UnaryOp::Negation>;
    using MinusExpr = Unary<UnaryOp::UnMinus>;
    using DerefExpr = Unary<UnaryOp::Deref>;
    
    template<std::size_t i , class T, class F, class... Args>
      constexpr auto  auto_index ()  {
      if constexpr ( std::is_same_v<T,F>) {
	  return i;
      }
      else {
	return auto_index<i+1,T,Args...> ();
      }
    }
    
    template<std::size_t i , class T, class F>
      constexpr auto  auto_index ()  {
      if constexpr ( std::is_same_v<T,F>) {
	  return i;
      }
      else {
	return []<bool b = false> {static_assert (b);}();
      }
    }

    template<class T>
    constexpr auto findExprIndex () {
      return auto_index<0,T,Constant,Register,AddExpr,SubExpr,DivExpr,MulExpr,LEqExpr,GEqExpr,EqExpr,NEqExpr,LtExpr,GtExpr,NegationExpr,MinusExpr,DerefExpr> (); 
    }
    
    
    template<BinOp op>
    Binary<op>::Binary (Expr_ptr&& l, Expr_ptr&& r) : Expr(findExprIndex<Binary<op>> ()), left(std::move(l)),right(std::move(r)) {}

    template<UnaryOp op>
    Unary<op>::Unary (Expr_ptr expr) : Expr(findExprIndex<Unary<op>> ()), right(expr) {
    }
    
    inline Constant::Constant (std::int8_t val) : Expr(findExprIndex<Constant> ()), value(val) {}
    inline Register::Register (std::size_t number, std::string name) : Expr(findExprIndex<Register> ()), registernumber(number),name(std::move(name)) {}

    template<class T>
    class ExprVisitor {
    public:
      virtual ~ExprVisitor () {}
      virtual T visitRegister (const Register& r) = 0;
      virtual T visitConstant (const Constant& r) = 0;
      virtual T visitAddExpr (const AddExpr& r) = 0;
      virtual T visitSubExpr (const SubExpr& r) = 0;
      virtual T visitDivExpr (const DivExpr& r) = 0;
      virtual T visitMulExpr (const MulExpr& r) = 0;
      virtual T visitLEqExpr (const LEqExpr& r) = 0;
      virtual T visitGEqExpr (const GEqExpr& r) = 0;
      virtual T visitNEqExpr (const NEqExpr& r) = 0;
      virtual T visitEqExpr (const EqExpr& r) = 0;
      virtual T visitLtExpr (const LtExpr& r) = 0;
      virtual T visitGtExpr (const GtExpr& r) = 0;
      virtual T visitNegationExpr (const NegationExpr& r) = 0;
      virtual T visitMinusExpr (const MinusExpr& r) = 0;
      virtual T visitDerefExpr (const DerefExpr& r) = 0;
      
      
      T visit (const Expr& e) {
	switch (e.exprType ()) {
	case findExprIndex<Register> ():
	  return visitRegister (static_cast<const Register&> (e));
	case findExprIndex<Constant> ():
	  return visitConstant (static_cast<const Constant&> (e));
	case findExprIndex<AddExpr> ():
	  return visitAddExpr (static_cast<const AddExpr&> (e));
	case findExprIndex<SubExpr> ():
	  return visitSubExpr (static_cast<const SubExpr&> (e));
	case findExprIndex<DivExpr> ():
	  return visitDivExpr (static_cast<const DivExpr&> (e));
	case findExprIndex<MulExpr> ():
	  return visitMulExpr (static_cast<const MulExpr&> (e));
	case findExprIndex<LEqExpr> ():
	  return visitLEqExpr (static_cast<const LEqExpr&> (e));
	case findExprIndex<GEqExpr> ():
	  return visitGEqExpr (static_cast<const GEqExpr&> (e));
	case findExprIndex<NEqExpr> ():
	  return visitNEqExpr (static_cast<const NEqExpr&> (e));
	case findExprIndex<EqExpr> ():
	  return visitEqExpr (static_cast<const EqExpr&> (e));
	case findExprIndex<LtExpr> ():
	  return visitLtExpr (static_cast<const LtExpr&> (e));
	case findExprIndex<GtExpr> ():
	  return visitGtExpr (static_cast<const GtExpr&> (e));
	case findExprIndex<NegationExpr> ():
	  return visitNegationExpr (static_cast<const NegationExpr&> (e));
	case findExprIndex<MinusExpr> ():
	  return visitMinusExpr (static_cast<const MinusExpr&> (e));
	case findExprIndex<DerefExpr> ():
	  return visitDerefExpr (static_cast<const DerefExpr&> (e));
	    
	default:
	  throw std::runtime_error ("Don't know how to visit this");
	}
      
      }
    };

  }
}

#endif 
