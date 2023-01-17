%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {FMTeach::Whiley}
%define api.parser.class {Parser}

%code requires{
  namespace FMTeach {
    namespace Whiley {
      class Scanner;
      class ASTBuilder;
    }
  }

// The following definitions is missing when %locations isn't used
#ifndef YY_NULLPTR
#if defined __cplusplus && 201103L <= __cplusplus
#define YY_NULLPTR nullptr
#else
#define YY_NULLPTR 0
#endif
#endif

#include <cstdint>
#include <string>
 
 }

%parse-param { FMTeach::Whiley::Scanner& scanner } {FMTeach::Whiley::ASTBuilder& builder }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
  #include "whiley/ast.hpp"
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
decl : VAR IDENTIFIER SEMI {builder.DeclareStmt ($2);}

stmtlist : stmtlist stmt {builder.SequenceStmt ();} | stmt
stmt : simpstmt  | selectivestmt | iterativestmt
selectivestmt : IF LPARAN expr RPARAN LBRACE stmtlist RBRACE ELSE LBRACE stmtlist RBRACE {builder.IfStmt ();}
iterativestmt : WHILE LPARAN expr RPARAN LBRACE stmtlist RBRACE {builder.WhileStmt ();}
simpstmt : IDENTIFIER ASS expr SEMI { builder.AssignStmt ($1);}
| SKIP SEMI {builder.SkipStmt ();}
expr : NUMBER {builder.NumberExpr ($1);} | IDENTIFIER {builder.IdentifierExpr ($1);}
%%


void  FMTeach::Whiley::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
