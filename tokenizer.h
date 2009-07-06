#ifndef _EXT_GRAMMAR_TOKENIZER_H
#define _EXT_GRAMMAR_TOKENIZER_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

#include "token.h"
#include "FlexLexer.h"

namespace grammar {

class Tokenizer: public yyFlexLexer {
 public:
  Tokenizer(std::istream& is, TokenFactory& tokenFactory) : 
    tokenFactory_(tokenFactory), yyFlexLexer(&is, &err_), 
    col_(1), offset_(1), token_(0) {}

  Token* next() {
    if (yylex() != 0) {
#ifdef _LEMONDEBUG    
      std::cout << *token_ << std::endl;
#endif    
      return token_;
    }
    err_ << std::flush;
    if (!err_.str().empty())
      throw unknown(err_.str(), col_, lineno(), offset_);
    throw eof();
  }

  size_t col() const { return col_; }
  size_t offset() const { return offset_; }
  
  class eof: public std::exception {
   public:
    explicit eof() {}
  };

  class unknown: public std::exception {
   public:
    explicit unknown(const std::string& token, size_t col, size_t line, 
                     size_t offset) : msg_(""), token_(token), col_(col), 
                                      line_(line), offset_(offset) {
      std::stringstream fmt;
      fmt << "unknown token '" << token_ << "' at the position " << col_
          << ", line " << line_ << ", offset " << offset_;
      msg_ = fmt.str();
    }

    virtual const char* what() const throw() { return msg_.c_str(); }

   private:
    std::string msg_;
    std::string token_;
    size_t col_;
    size_t line_;
    size_t offset_;
  };

 private:
  virtual int create_token(int token) {
    token_ = tokenFactory_.createToken(token, yytext);
    skip_token();
    return token_->token();
  }

  virtual void skip_token() {
    col_ += yyleng;
    offset_ += yyleng;
  }

  virtual void next_line() {
    col_ = 0;
  }

  TokenFactory& tokenFactory_;
  size_t col_;
  size_t offset_;
  Token* token_;
  std::stringstream err_;

  Tokenizer(const Tokenizer&);
  void operator=(const Tokenizer&);
};

} // namespace

#endif
