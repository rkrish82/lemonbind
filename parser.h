#ifndef _EXT_GRAMMAR_PARSER
#define _EXT_GRAMMAR_PARSER

#include <string>
#include <iostream>
#include <exception>

#include "tokenizer.h"

namespace grammar {

class Parser {
 public:
  Parser(std::istream& is, Tokenizer& tokenizer) : tokenizer_(tokenizer) {}
  void parse();

  class ParsingInterrupted: public std::exception {
   public:
    ParsingInterrupted() {}
  };
  
  class SyntaxError: public std::exception {
   public:
    SyntaxError(const std::string& msg) : std::exception(msg.c_str()) {}
  };

 private:
  Tokenizer& tokenizer_;
};

} // grammar

#endif
