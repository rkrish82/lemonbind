#include "gtest/gtest.h"
#include <sstream>

#include "tokenizer.h"
#include "mock_token.h"

using namespace grammar;

TEST(Tokenizer, SimpleSelect) {
  try {
    std::stringstream fmt;
    fmt.str("SELECT col FROM table");
    MockTokenFactory mockTokenFactory;
    Tokenizer tokenizer(fmt, mockTokenFactory);
    EXPECT_EQ(MockToken(MockToken::kSelect), *tokenizer.next());
    EXPECT_EQ(MockToken(MockToken::kName, "col"), *tokenizer.next());
    EXPECT_EQ(MockToken(MockToken::kFrom), *tokenizer.next());
    EXPECT_EQ(MockToken(MockToken::kName, "table"), *tokenizer.next());
  } catch (const Tokenizer::eof&) {
    FAIL();
  } catch (const Tokenizer::unknown& e) {
    FAIL() << e.what();
  }
}

TEST(Tokenizer, MultiColumnSelect) {
  try {
    std::stringstream fmt;
    fmt.str("SELECT col1, col2 FROM table");
    MockTokenFactory mockTokenFactory;
    Tokenizer tokenizer(fmt, mockTokenFactory);
    EXPECT_EQ(MockToken(MockToken::kSelect), *tokenizer.next());
    EXPECT_EQ(MockToken(MockToken::kName, "col1"), *tokenizer.next());
    EXPECT_EQ(MockToken(MockToken::kComma, ","), *tokenizer.next());
    EXPECT_EQ(MockToken(MockToken::kName, "col2"), *tokenizer.next());
    EXPECT_EQ(MockToken(MockToken::kFrom), *tokenizer.next());
    EXPECT_EQ(MockToken(MockToken::kName, "table"), *tokenizer.next());
  } catch (const Tokenizer::eof&) {
    FAIL();
  } catch (const Tokenizer::unknown& e) {
    FAIL() << e.what();
  }
}

TEST(Tokenizer, EndOfFile) {
  try {
    std::stringstream fmt;
    fmt.str("SELECT");
    MockTokenFactory mockTokenFactory;
    Tokenizer tokenizer(fmt, mockTokenFactory);
    EXPECT_EQ(MockToken(MockToken::kSelect), *tokenizer.next());
    EXPECT_EQ(MockToken(MockToken::kFrom), *tokenizer.next());
    FAIL();
  } catch (const Tokenizer::eof&) {
  } catch (const Tokenizer::unknown& e) {
    FAIL() << e.what();
  }
}

TEST(Tokenizer, UnknownToken) {
  std::stringstream fmt;
  MockTokenFactory mockTokenFactory;
  Tokenizer tokenizer(fmt, mockTokenFactory);
  try {
    fmt.str("SELECT\n123");
    EXPECT_EQ(MockToken(MockToken::kSelect), *tokenizer.next());
    EXPECT_EQ(MockToken(MockToken::kFrom), *tokenizer.next());
    FAIL();
  } catch (const Tokenizer::eof&) {
    FAIL();
  } catch (const Tokenizer::unknown& e) {
    EXPECT_EQ(std::string(
      "unknown token '123' at the position 1, line 2, offset 8"), e.what());
  }
}
