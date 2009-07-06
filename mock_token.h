#ifndef _MOCK_TOKEN_H
#define _MOCK_TOKEN_H

#include "token.h"
#include "parser_unittest_grammar.h"

class MockToken: public grammar::Token {
 public:
  explicit MockToken(int token) : grammar::Token(token) {
    value_ = descr();
  }
  MockToken(int token, const std::string& value) : grammar::Token(token, value) 
    {}

  const static int kNewline = NEWLINE;
  const static int kSelect = SELECT;
  const static int kFrom = FROM;
  const static int kOrderby = ORDERBY;
  const static int kName = NAME;
  const static int kComma = COMMA;
  const static int kLeftParent = LPARENT;
  const static int kRightParent = RPARENT;

  virtual const char* descr() const {
    switch (token()) {
      case kNewline: return "NEWLINE";
      case kSelect: return "SELECT";
      case kFrom: return "FROM";
      case kOrderby: return "ORDERBY";
      case kName: return "NAME";
      case kComma: return "COMMA";
      case kLeftParent: return "LPARENT";
      case kRightParent: return "RPARENT";
    }
    return "?";
  }
};

class MockTokenFactory: public grammar::TokenFactory {
 public:
  virtual grammar::Token* createToken(int token, const char* value) {
    return new MockToken(token, value);
  }
};

#endif
