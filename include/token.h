#pragma once

#include <iostream>

using std::string;

enum Tag {
  TYPE = 256,
  KEYWORD,

  // Literals
  LITERAL_BOOLEAN,
  LITERAL_CHAR,
  LITERAL_FLOAT,
  LITERAL_INTEGER,

  // Operator
  OPERATOR,
};

class Token {
 public:
  Token() : tag(0) {}
  Token(char character) : tag(int(character)), lexeme({character}) {}
  Token(int tag, string lexeme) : tag(tag), lexeme(lexeme) {}
  virtual string toString();

 private:
  uint tag;
  string lexeme;
};
