#include "gtest/gtest.h"
#include <string>
#include <sstream>

#include "mock_token.h"

TEST(Token, Constructor) {
  MockToken token1(100, "main");
  EXPECT_EQ(100, token1.token());
  EXPECT_EQ(std::string("main"), token1.value());
  MockToken token2(101);
  EXPECT_EQ(101, token2.token());
  EXPECT_EQ(std::string("?"), token2.value());
}

TEST(Token, CopyConstructor) {
  MockToken token1(100, "main");
  MockToken token2(token1);
  EXPECT_EQ(100, token2.token());
  EXPECT_EQ(std::string("main"), token2.value());
  MockToken token3 = token1;
  EXPECT_EQ(100, token3.token());
  EXPECT_EQ(std::string("main"), token3.value());
}

TEST(Token, AssignOperator) {
  MockToken token1(100, "main");
  MockToken token2(101, "test");
  token2 = token1;
  EXPECT_EQ(100, token2.token());
  EXPECT_EQ(std::string("main"), token2.value());
}

TEST(Token, EqualOperator) {
  MockToken token1(101, "test");
  MockToken token2(101, "test");
  EXPECT_EQ(token1, token2);
  MockToken token3(100, "main");
  EXPECT_FALSE(token1 == token3);
}

TEST(Token, NotEqualOperator) {
  MockToken token1(100, "main");
  MockToken token2(101, "test");
  EXPECT_NE(token1, token2);
  MockToken token3(100, "main");
  EXPECT_FALSE(token1 != token3);
}

TEST(Token, StreamOutput) {
  std::stringstream fmt;
  MockToken token1(MockToken::kSelect, "SELECT");
  fmt << token1;
  EXPECT_EQ(std::string("token: SELECT (2) [SELECT]"), fmt.str());
  fmt.str("");
  MockToken token2(-1, "What?");
  fmt << token2;
  EXPECT_EQ(std::string("token: ? (-1) [What?]"), fmt.str());
  fmt.str("");
  MockToken token3(MockToken::kFrom);
  fmt << token3;
  EXPECT_EQ(std::string("token: FROM (3) [FROM]"), fmt.str());
}
