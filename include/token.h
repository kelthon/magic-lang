#pragma once

#include <iostream>

using std::string;

enum TokenType {
  TK_EOF = -1,

  // Types
  TK_TYPE_INT = -2,
  TK_TYPE_BOOL = -3,
  TK_TYPE_CHAR = -4,
  TK_TYPE_FLOAT = -5,
  TK_TYPE_DOUBLE = -6,
  TK_TYPE_STRING = -7,
  TK_TYPE_CLASS = -8,

  // Identifiers
  TK_IDENTIFIER = -9,

  // Keywords
  TK_IF = -10,
  TK_ELSE = -11,
  TK_WHILE = -12,
  TK_FOR = -13,
  TK_RETURN = -14,

  // Literals
  TK_LITERAL_INT = -15,
  TK_LITERAL_BOOL = -16,
  TK_LITERAL_CHAR = -17,
  TK_LITERAL_FLOAT = -18,
  TK_LITERAL_DOUBLE = -19,
  TK_LITERAL_STRING = -20,
  TK_LITERAL_CLASS = -21,
  TK_LITERAL_NULL = -22,

  // Operators
  TK_OPERATOR = -23,

  // Access modifiers
  TK_ACCESS_MODIFIER = -24,

  // Modifiers
  TK_MODIFIER = -25,

  // Object Instance
  TK_OBJ_INSTANCE = -26,
};

class Token {
 public:
  Token() = default;
  Token(char character) : type(int(character)), lexeme({character}) {}
  Token(int type, string lexeme) : type(type), lexeme(lexeme) {}

  int getType() { return type; }
  string getLexeme() { return lexeme; }

  static bool isType(int tag);
  static bool isLiteral(int tag);

  virtual string toString();

 private:
  int type;
  string lexeme;
};
