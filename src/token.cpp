#include "token.h"

#include <sstream>
using std::stringstream;

void Token::updatePosition(uint line, uint column) {
  this->line = line;
  this->column = column;
}

string Token::toString() {
  stringstream buffer;

  buffer << "<" << lexeme << ">";

  return buffer.str();
}
