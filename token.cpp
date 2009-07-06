#include "token.h"

std::ostream& operator<<(std::ostream& os, const grammar::Token& token) {
  os << "token: " << token.descr() << " (" << token.token() << ")";
  if (!token.value().empty())
    os <<" [" << token.value() << "]";
  return os;
}
