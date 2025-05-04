#include "token.h"

#include <sstream>
using std::stringstream;

string Token::toString() {
  stringstream buffer;

  buffer << "<" << lexeme << ">";

  return buffer.str();
}

bool isTypeDeclaration(Token *token) {
  switch (token->getType()) {
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
