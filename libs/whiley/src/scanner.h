#ifndef __SCANNER_HPP__
#define __SCANNER_HPP__ 

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.hh"
#include "location.hh"

namespace FMTeach {
  namespace Whiley {
    
    class Scanner : public yyFlexLexer{
    public:
      
    Scanner(std::istream *in) : yyFlexLexer(in) {
      //loc = new FMTeach::Whiley::Parser::location_type();
    };
      
      //get rid of override virtual function warning
      using FlexLexer::yylex;
      
      virtual int yylex( FMTeach::Whiley::Parser::semantic_type * const lval, 
			 FMTeach::Whiley::Parser::location_type *location );   
      
    private:
      /* yyval ptr */
      FMTeach::Whiley::Parser::semantic_type *yylval = nullptr;
      /* location ptr */
      FMTeach::Whiley::Parser::location_type *loc    = nullptr;
    };

  }
} /* end namespace MC */

#endif 
