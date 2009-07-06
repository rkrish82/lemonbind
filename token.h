#ifndef _EXT_GRAMMAR_TOKEN
#define _EXT_GRAMMAR_TOKEN

#include <string>
#include <iostream>

namespace grammar {

class Token {
 public:
  explicit Token(int token) : token_(token), value_("") {}
  Token(int token, const std::string& value) : token_(token), value_(value) {}
  Token(const Token& rhs) { copy(rhs); }
  void operator=(const Token& rhs) { copy(rhs); }
  virtual bool operator==(const Token& rhs) const {
    return token_ == rhs.token_ && value_ == rhs.value_;
  }
  virtual bool operator!=(const Token& rhs) const {
    return !operator==(rhs);
  }
  int token() const { return token_; }
  const std::string& value() const { return value_; }
  virtual const char* descr() const = 0;
 protected:
  int token_;
  std::string value_;
 private:
  void copy(const Token& rhs) {
    token_ = rhs.token_;
    value_ = rhs.value_;
  }
};

class TokenFactory {
 public:
  virtual Token* createToken(int token, const char* value) = 0;
};

} // grammar

std::ostream& operator<<(std::ostream& os, const grammar::Token& token);

#endif
