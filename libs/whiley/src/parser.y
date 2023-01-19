%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {FMTeach::Whiley}
%define api.parser.class {Parser}
%define api.location.type {FMTeach::Whiley::location_t}


%code requires{
  namespace FMTeach {
    namespace Whiley {
      class Scanner;
      class ASTBuilder;
    }
  }



#include <cstdint>
#include <string>
#include "whiley/ast.hpp" 
 }

%parse-param { FMTeach::Whiley::Scanner& scanner } {FMTeach::Whiley::ASTBuilder& builder }
%initial-action
{

};

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include "scanner.h"
#undef yylex
#define yylex scanner.yylex
  
}

%define api.value.type variant
%define parse.assert

%token    VAR
%token    WHILE
%token    IF
%token    ELSE
%token    SKIP
%token    PLUS
%token    MINUS
%token    DIV
%token    MUL
%token    LEQ
%token    GEQ
%token    LT
%token    GT
%token    EQ
%token    NEQ
%token    ASS
%token    SEMI
%token    LPARAN
%token    RPARAN
%token    LBRACE
%token    RBRACE

%token END 0 "end of file"
%token <std::string>    IDENTIFIER
%token <std::int8_t>    NUMBER

%locations

%%

prgm : decllist stmtlist  {}
decllist :  decllist decl | decl
decl : VAR IDENTIFIER SEMI { builder.DeclareStmt ($2,@$);}

stmtlist : stmtlist stmt {builder.SequenceStmt (@$);} | stmt

stmt : simpstmt  | selectivestmt | iterativestmt

selectivestmt : IF LPARAN expr RPARAN LBRACE stmtlist RBRACE ELSE LBRACE stmtlist RBRACE {builder.IfStmt (@$);}
              | IF LPARAN expr RPARAN LBRACE stmtlist RBRACE {builder.SkipStmt (@$);builder.IfStmt (@$);}

iterativestmt : WHILE LPARAN expr RPARAN LBRACE stmtlist RBRACE {builder.WhileStmt (@$);}

simpstmt : IDENTIFIER ASS expr SEMI { builder.AssignStmt ($1,@$);}
| SKIP SEMI {builder.SkipStmt (@$);}

expr : arith_expr | bool_expr

bool_expr    : arith_expr LEQ arith_expr{builder.BinaryExpr (FMTeach::Whiley::BinOps::LEq,@$);}
             | arith_expr GEQ arith_expr{builder.BinaryExpr (FMTeach::Whiley::BinOps::GEq,@$);}
             | arith_expr LT arith_expr{builder.BinaryExpr (FMTeach::Whiley::BinOps::Lt,@$);}
             | arith_expr GT arith_expr{builder.BinaryExpr (FMTeach::Whiley::BinOps::Gt,@$);}
             | arith_expr EQ arith_expr{builder.BinaryExpr (FMTeach::Whiley::BinOps::Eq,@$);}
             | arith_expr NEQ arith_expr{builder.BinaryExpr (FMTeach::Whiley::BinOps::NEq,@$);}
arith_expr   : arith_expr PLUS arith_term {builder.BinaryExpr (FMTeach::Whiley::BinOps::Add,@$);}
             | arith_expr MINUS arith_term {builder.BinaryExpr (FMTeach::Whiley::BinOps::Sub,@$);}
             | arith_term
	     
arith_term   : arith_term MUL arith_factor {builder.BinaryExpr (FMTeach::Whiley::BinOps::Mul,@$);}
             | arith_term DIV arith_factor {builder.BinaryExpr (FMTeach::Whiley::BinOps::Div,@$);}
             | arith_factor
arith_factor : NUMBER {builder.NumberExpr ($1,@$);}
             | IDENTIFIER {builder.IdentifierExpr ($1,@$);}
             | LPARAN expr RPARAN  

%%


void  FMTeach::Whiley::Parser::error( const location_type& l, const std::string &err_message )
{
  std::cerr << "Error: " << err_message << " at " << l << "\n";
}
