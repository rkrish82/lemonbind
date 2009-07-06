#include "gtest/gtest.h"
#include <iostream>
#include <sstream>
#include <exception>

#include "mock_token.h"
#include "tokenizer.h"
#include "parser.h"

using namespace grammar;

TEST(Parser, NestedSelect) {
  try {
    std::stringstream fmt;
    fmt.str("SELECT col1, col2, col3 FROM (SELECT sub1, sub2 FROM table)");
    MockTokenFactory mockTokenFactory;
    Tokenizer tokenizer(fmt, mockTokenFactory);
    Parser parser(fmt, tokenizer);
    parser.parse();
  } catch (const Parser::SyntaxError& e) {
    FAIL() << e.what();
  }
}

TEST(Parser, SimpleSelect) {
  try {
    std::stringstream fmt;
    fmt.str("SELECT col1, col2, col3 FROM table1, table2, table3");
    MockTokenFactory mockTokenFactory;
    Tokenizer tokenizer(fmt, mockTokenFactory);
    Parser parser(fmt, tokenizer);
    parser.parse();
  } catch (const Parser::SyntaxError& e) {
    FAIL() << e.what();
  }
}

TEST(Parser, SimpleSelectSyntaxErrorAtLast) {
  try {
    std::stringstream fmt;
    fmt.str("SELECT col1, col2, col3 FROM table1, table2, table3 ###");
    MockTokenFactory mockTokenFactory;
    Tokenizer tokenizer(fmt, mockTokenFactory);
    Parser parser(fmt, tokenizer);
    parser.parse();
    FAIL();
  } catch (const Parser::SyntaxError& e) {
    EXPECT_STREQ("unknown token '###' at the position 53, line 1, offset 53", 
                 e.what());
  }
}

TEST(Parser, SimpleSelectOrderby) {
  try {
    std::stringstream fmt;
    fmt.str("SELECT col1, col2, col3 FROM table1, table2, table3 ORDERBY col1, col2");
    MockTokenFactory mockTokenFactory;
    Tokenizer tokenizer(fmt, mockTokenFactory);
    Parser parser(fmt, tokenizer);
    parser.parse();
  } catch (const Parser::SyntaxError& e) {
    FAIL() << e.what();
  }
}

TEST(Parser, SimpleSelectParseError) {
  try {
    std::stringstream fmt;
    fmt.str("SELECT SELECT col FROM table");
    MockTokenFactory mockTokenFactory;
    Tokenizer tokenizer(fmt, mockTokenFactory);
    Parser parser(fmt, tokenizer);
    parser.parse();
    FAIL() << "Parsing must fail";
  } catch (const Parser::SyntaxError& e) {
    EXPECT_STREQ("syntax error at the position 14 line 1 (offset 14)",
                 e.what());
  }
}

TEST(Parser, SimpleSelectUnknownTokenError) {
  try {
    std::stringstream fmt;
    fmt.str("123 SELECT col FROM table");
    MockTokenFactory mockTokenFactory;
    Tokenizer tokenizer(fmt, mockTokenFactory);
    Parser parser(fmt, tokenizer);
    parser.parse();
    FAIL();
  } catch (const Parser::SyntaxError& e) {
    EXPECT_STREQ("unknown token '123' at the position 23, line 1, offset 23", 
                 e.what());
  }
}
