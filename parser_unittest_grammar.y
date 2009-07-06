%include {
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "mock_token.h"
#include "parser.h"

#define _xLEMONDEBUG

typedef std::vector<std::string> Items;

void token_destructor(grammar::Token* token) {
#ifdef _LEMONDEBUG
  std::cout << "token_destructor(): " << *token << std::endl;
#endif 
  delete token;
}

std::ostream& operator<<(std::ostream& os, const Items& items) {
  for (Items::const_iterator i = items.begin(); i != items.end(); ++i)
    os << "'" << *i << "' ";
  return os;
}

} /* %include */

%token_type {grammar::Token*}

%token_destructor { token_destructor($$); }

// This method is called then the parser needs to dispose an item
// of the 'columns_list' type.
%destructor columns_list {
#ifdef _LEMONDEBUG
  std::cout << "columns_list type destructor: " << *$$ << std::endl;
#endif
  delete $$;
}

// This method is called then the parser needs to dispose an item
// of the 'tables_list' type.
%destructor tables_list {
#ifdef _LEMONDEBUG
  std::cout << "tables_list type destructor: " << *$$ << std::endl;
#endif	
  delete $$;
}

// This method is called then the parser needs to dispose an item
// of the 'select_op' type.
%destructor select_op {
#ifdef _LEMONDEBUG
  std::cout << "select_op type destructor: " << *$$ << std::endl;
#endif	
  delete $$;
}

%default_type {grammar::Token*}

%type columns_list {Items*}
%type tables_list {Items*}
%type select_op {Items*}

%parse_accept {
}

%syntax_error {
  throw grammar::Parser::ParsingInterrupted();
}

main ::= program.
program ::= select_op.
program ::= program NEWLINE select_op. 

select_op(C) ::= SELECT columns_list(A) FROM tables_list(B). {
  std::cout << "SELECT:" << std::endl
            << "  COLUMNS: " << *A << std::endl
            << "  TABLES: " << *B << std::endl;
  C = new Items();
  C->push_back("123");            
  C->push_back("456");            
}

select_op(D) ::= SELECT columns_list(A) FROM tables_list(B) ORDERBY columns_list(C). {
  std::cout << "SELECT:" << std::endl
            << "  COLUMNS: " << *A << std::endl
            << "  TABLES: " << *B << std::endl
            << "  ORDEY BY: " << *C << std::endl;
  D = new Items();
  D->push_back("aa");            
  D->push_back("bb");            
  D->push_back("cc");            
}

columns_list(A) ::= NAME(B). { 
#ifdef _LEMONDEBUG
  std::cout << "* init columns list" << std::endl;
  std::cout << "Added the first item: " << *B << std::endl;
#endif	
  A = new Items();
  A->push_back(B->value());
}

columns_list(A) ::= columns_list(C) COMMA NAME(B). { 
#ifdef _LEMONDEBUG
  std::cout << "Insert to the columm list (" << C->size() << "): " << *B << std::endl;	
#endif	
  C->push_back(B->value());  
  A = C;
}

tables_list(A) ::= NAME(B). { 
#ifdef _LEMONDEBUG
  std::cout << "* init tables list" << std::endl;
  std::cout << "Added the first item: " << *B << std::endl;
#endif	
  A = new Items();
  A->push_back(B->value());
}

tables_list(A) ::= tables_list(C) COMMA NAME(B). { 
#ifdef _LEMONDEBUG
  std::cout << "Insert to the table list (" << C->size() << "): " << *B << std::endl;	
#endif	
  C->push_back(B->value());  
  A = C;
}

tables_list(A) ::= LPARENT select_op(B) RPARENT. {
  std::cout << "Table list from SELECT: " << *B << std::endl;
  A = new Items(*B);
}
