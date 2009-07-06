%{
#include "mock_token.h"
%}

%option yylineno
%option nounistd
%option default warn
%option noyywrap
%option c++

letter     [a-zA-Z]
dec        [0-9]
alphanum   ({letter}|{dec})
identifier ({alphanum}|"_")

%%

"SELECT" { 
  return create_token(MockToken::kSelect);
}

"FROM" { 
  return create_token(MockToken::kFrom);
}

"ORDERBY" { 
  return create_token(MockToken::kOrderby);
}

"_"*{letter}{identifier}*("."_*{letter}{identifier}*)? { 
  return create_token(MockToken::kName); 
}

"," { 
  return create_token(MockToken::kComma);
}

"(" {
  return create_token(MockToken::kLeftParent);
}

")" {
  return create_token(MockToken::kRightParent);
}
  
[ \t]  { 
  skip_token();
}

\n { 
  next_line();
  skip_token();
}

%%

// Additional C/C++ code could added here.
