#include "lexer.h"

#include <iostream>
#include <sstream>

#include "error.h"
#include "file_reader.h"
#include "langdef.h"
#include "token.h"

using std::stringstream;

/**
 * @brief Lexer constructor
 * @note It initializes the token table with keywords, types and literals
 * @note It initializes the peek character with a space character
 */
Lexer::Lexer() {
  // Types
  tokenTable["int"] = Token(TK_TYPE_INT, "int");
  tokenTable["bool"] = Token(TK_TYPE_BOOL, "bool");
  tokenTable["char"] = Token(TK_TYPE_CHAR, "char");
  tokenTable["float"] = Token(TK_TYPE_FLOAT, "float");
  tokenTable["double"] = Token(TK_TYPE_DOUBLE, "double");
  tokenTable["string"] = Token(TK_TYPE_STRING, "string");
  tokenTable["class"] = Token(TK_TYPE_CLASS, "class");

  // Keywords
  tokenTable["if"] = Token(TK_IF, "if");
  tokenTable["else"] = Token(TK_ELSE, "else");
  tokenTable["while"] = Token(TK_WHILE, "while");
  tokenTable["for"] = Token(TK_FOR, "for");
  tokenTable["return"] = Token(TK_RETURN, "return");

  // Object Instance
  tokenTable["new"] = Token(TK_OBJ_INSTANCE, "new");
  tokenTable["this"] = Token(TK_OBJ_INSTANCE, "this");
  tokenTable["super"] = Token(TK_OBJ_INSTANCE, "super");

  // Access Modifiers
  tokenTable["public"] = Token(TK_ACCESS_MODIFIER, "public");
  tokenTable["private"] = Token(TK_ACCESS_MODIFIER, "private");
  tokenTable["protected"] = Token(TK_ACCESS_MODIFIER, "protected");

  // Modifiers
  tokenTable["static"] = Token(TK_MODIFIER, "static");
  tokenTable["abstract"] = Token(TK_MODIFIER, "abstract");
  tokenTable["readonly"] = Token(TK_MODIFIER, "readonly");
  tokenTable["override"] = Token(TK_MODIFIER, "override");
  tokenTable["final"] = Token(TK_MODIFIER, "final");

  // Literals
  tokenTable["null"] = Token(TK_LITERAL_NULL, "null");
  tokenTable["true"] = Token(TK_LITERAL_BOOL, "true");
  tokenTable["false"] = Token(TK_LITERAL_BOOL, "false");

  peek = SPACE_CHAR;
}

/**
 *  @brief Skips white spaces, new lines and tabs
 * @note It is used to skip white spaces in the source code
 */
void Lexer::skipWhiteSpaces() {
  while (isspace(peek)) {
    peek = reader.getChar();
  }
}

/// @brief Gets numbers and sets in lexer token
void Lexer::nextNumber() {
  stringstream stream;
  int type = TK_LITERAL_INT;
  bool isFloatNumber = false;
  bool isDoubleNumber = false;

  while (isdigit(peek) || peek == DECIMAL_POINT_CHAR ||
         peek == FLOAT_INDICATOR) {
    if (peek == DECIMAL_POINT_CHAR) {
      // The number is invalid;
      if (isDoubleNumber || isFloatNumber) {
        throw SyntaxError(
            "A period ('.') is already present in the number "
            "and cannot be used again.");
        break;
      }
      type = TK_LITERAL_DOUBLE;
      isDoubleNumber = true;
    }

    if (peek == FLOAT_INDICATOR) {
      // The number is invalid;
      if (isFloatNumber) {
        throw SyntaxError(
            "A floating-point number cannot contain multiple "
            "'f' characters.");
        break;
      }

      type = TK_LITERAL_FLOAT;
      isFloatNumber = true;
    }

    stream << peek;
    peek = reader.getChar();
  }

  token = Token(type, stream.str());
}

/// @brief Gets keywords and reserved words and sets in lexer token
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
    token = Token(TK_IDENTIFIER, word);
    tokenTable[word] = token;
  }
}

/// @brief Gets operators and sets in lexer token
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
    token = Token(TK_OPERATOR, symbol);
  }
}

/**
 * @brief Gets the next token
 *  @return Pointer to the token
 * @note If the token is not valid, it returns nullptr
 * @note If the token is EOF, it returns nullptr
 * @note If the token is a comment, it returns nullptr
 */
Token* Lexer::scan() {
  if (isspace(peek)) {
    skipWhiteSpaces();
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

/**
 * @brief Checks if the end of the file is reached
 * @return true if the end of the file is reached, false otherwise
 */
bool Lexer::end() { return peek == TK_EOF; }
