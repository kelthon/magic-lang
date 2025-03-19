#include "lexer.h"

#include <iostream>
#include <sstream>

#include "file_reader.h"
#include "langdef.h"
#include "token.h"

using std::stringstream;

Lexer::Lexer() {
  tokenTable["class"] = Token(Tag::KEYWORD, "class");
  tokenTable["int"] = Token(Tag::TYPE, "int");
  tokenTable["bool"] = Token(Tag::TYPE, "bool");
  tokenTable["char"] = Token(Tag::TYPE, "char");
  tokenTable["float"] = Token(Tag::TYPE, "float");

  peek = SPACE_CHAR;
}

/// @brief Removes white spaces
void Lexer::removeWhiteSpaces() {
  while (isspace(peek)) {
    peek = reader.getChar();
  }
}

/// @brief Gets numbers and sets token
void Lexer::nextNumber() {
  stringstream stream;
  bool isFloatNumber = false;
  int type = Tag::LITERAL_INTEGER;

  while (isdigit(peek) || peek == DECIMAL_POINT_CHAR) {
    if (peek == DECIMAL_POINT_CHAR) {
      // The number is invalid;
      if (isFloatNumber) {
        /// @todo: throw a syntax error
        break;
      }
      type = Tag::LITERAL_FLOAT;
      isFloatNumber = true;
    }

    stream << peek;
    peek = reader.getChar();
  }

  token = Token(type, stream.str());
}

/// @brief Gets keywords and reserved words and sets token
void Lexer::nextIdentifier() {
  string word;
  stringstream stream;

  while (isalnum(peek)) {
    stream << peek;
    peek = reader.getChar();
  }
  word = stream.str();

  auto iterator = tokenTable.find(word);

  if (iterator != tokenTable.end()) {
    token = iterator->second;
  } else {
    token = Token(Tag::TYPE, word);
    tokenTable[word] = token;
  }
}

/// @brief Gets operators and sets token
void Lexer::nextSymbol() {
  string symbol;
  stringstream stream;

  while (issymbol(peek)) {
    stream << peek;
    peek = reader.getChar();
  }

  symbol = stream.str();

  if (symbol.length() == 1) {
    token = Token(symbol[0]);
  }

  else {
    token = Token(Tag::OPERATOR, symbol);
  }
}

Token* Lexer::scan() {
  if (isspace(peek)) {
    removeWhiteSpaces();
  }

  if (isdigit(peek)) {
    nextNumber();
  }

  else if (isalpha(peek)) {
    nextIdentifier();
  }

  else if (issymbol(peek)) {
    nextSymbol();
  }

  else {
    return nullptr;
  }

  return &token;
}

bool Lexer::end() { return peek == EOF; }
