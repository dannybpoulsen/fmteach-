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

%parse-param { FMTeach::Whiley::Scanner  &scanner  }

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

%token <std::string>    IDENTIFIER
%token <std::int8_t>    NUMBER
%token    END    0     "end of file"
%token    LOWER


%locations

%%

prgm : decllist stmtlist {}
decllist :  decllist decl | decl
decl : VAR IDENTIFIER SEMI {}

stmtlist : stmtlist stmt | stmt
stmt : simpstmt  | selectivestmt | iterativestmt
selectivestmt : IF LPARAN expr RPARAN LBRACE stmtlist RBRACE
iterativestmt : WHILE LPARAN expr RPARAN LBRACE stmtlist RBRACE
simpstmt : IDENTIFIER ASS expr SEMI{}
expr : NUMBER {}
%%


void  FMTeach::Whiley::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
