#pragma once

#include <iostream>

using std::string;
using std::cout;

enum Tag {
  TYPE = 256,
  KEYWORD,

  // Literals
  LITERAL_BOOLEAN,
  LITERAL_CHAR,
  LITERAL_FLOAT,
  LITERAL_INTEGER,

  // Operators
  SIMPLE_ASSIGN
};

class Token {
 public:
  Token() : tag(0) {}
  Token(char character) : tag(int(character)), lexeme({character}) {}
  Token(int tag, string lexeme) : tag(tag), lexeme(lexeme) {}
  virtual void toString() { cout << "<" << tag << ", " << lexeme <<">";}

 private:
  uint tag;
  string lexeme;
};
