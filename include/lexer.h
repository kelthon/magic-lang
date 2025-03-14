#pragma once

#include <iostream>
#include <unordered_map>

#include "file_reader.h"
#include "token.h"

using std::string;
using std::unordered_map;

class Lexer {
 private:
  char peek;
  Token token;
  FileReader reader;
  unordered_map<string, Token> tokenTable;

  void removeWhiteSpaces();
  void getNumber();
  void getIdentifier();
  void getOperator();

 public:
  Lexer();
  Token* scan();
};