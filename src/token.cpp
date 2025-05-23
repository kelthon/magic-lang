#include "token.h"

#include <sstream>
using std::stringstream;

string Token::toString() {
  stringstream buffer;

  buffer << "<" << lexeme << ">";

  return buffer.str();
}

bool Token::isType(int tag) {
  switch (tag) {
    case TK_TYPE_INT:
    case TK_TYPE_BOOL:
    case TK_TYPE_CHAR:
    case TK_TYPE_FLOAT:
    case TK_TYPE_DOUBLE:
    case TK_TYPE_STRING:
      return true;

    default:
      return false;
  }
}

bool Token::isLiteral(int tag) {
  switch (tag) {
    case TK_LITERAL_INT:
    case TK_LITERAL_BOOL:
    case TK_LITERAL_CHAR:
    case TK_LITERAL_FLOAT:
    case TK_LITERAL_DOUBLE:
    case TK_LITERAL_STRING:
    case TK_LITERAL_CLASS:
    case TK_LITERAL_NULL:
      return true;

    default:
      return false;
  }
}
