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

  peek = reader.getchar();
}

/// @brief Removes white spaces
void Lexer::removeWhiteSpaces() {
  while (isspace(peek)) {
    peek = reader.getchar();
  }
}

/// @brief Gets numbers and sets token
void Lexer::getNumber() {
  int type = Tag::LITERAL_INTEGER;
  stringstream stream;
  bool isFloatNumber = false;

  while (isdigit(peek) || peek == DECIMAL_POINT_CHAR) {
    if (peek == DECIMAL_POINT_CHAR) {
      // The number is invalid;
      if (isFloatNumber) {
        /// @todo: throw a syntax error
        break;
      }
      type = Tag::LITERAL_FLOAT;
      isFloatNumber = true;

      stream << peek;
      peek = reader.getchar();
    }
  }

  token = Token(type, stream.str());
}

/// @brief Gets keywords and reserved words and sets token
void Lexer::getIdentifier() {
  string word;
  stringstream stream;

  while (isalpha(peek)) {
    stream << peek;
    peek = reader.getchar();
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
void Lexer::getOperator() {
  string op;
  stringstream stream;

  while (isoperator(peek)) {
    stream << peek;
    peek = reader.getchar();
  }

  op = stream.str();

  switch (op[0]) {
    case SIMPLE_ASSIGN_OPERATOR:
      token = Token(Tag::SIMPLE_ASSIGN, op);
      break;

    default:
      /// @todo: throw a syntax error
      break;
  }
}

Token* Lexer::scan() {
  if (isspace(peek)) removeWhiteSpaces();
  if (isdigit(peek)) getNumber();
  if (isalpha(peek)) getIdentifier();
  if (isoperator(peek)) getOperator();

  return &token;
}
