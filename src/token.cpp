#include "token.h"

#include <sstream>
using std::stringstream;

string Token::toString() {
  stringstream buffer;

  buffer << "<" << lexeme << ">";

  return buffer.str();
}
