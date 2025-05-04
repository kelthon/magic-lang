#pragma once

#include <iostream>
#include <unordered_map>

#include "file_reader.h"
#include "token.h"

using std::string;
using std::unordered_map;

/**
 * @brief Lexer class
 * @note This class is responsible for scanning and tokenizing the source code
*/ 
class Lexer {
  private:
    char peek;
    Token token;
    FileReader reader;
    unordered_map<string, Token> tokenTable;

    void skipWhiteSpaces();
    void nextNumber();
    void nextIdentifier();
    void nextSymbol();

  public:
    Lexer();
    Token* scan();
    bool end();
};