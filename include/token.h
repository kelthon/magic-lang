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
  Token(char character, uint line, uint column)
      : tag(int(character)), lexeme({character}), line(line), column(column) {}
  Token(int tag, string lexeme) : tag(tag), lexeme(lexeme) {}
  Token(int tag, string lexeme, uint line, uint column)
      : tag(tag), lexeme(lexeme), line(line), column(column) {}
  void updatePosition(uint line, uint column);
  virtual string toString();

 private:
  uint tag;
  string lexeme;
  uint line, column;
};
