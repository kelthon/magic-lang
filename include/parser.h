#pragma once

#include <functional>
#include <iostream>
#include <memory>

#include "ast.h"
#include "lexer.h"
#include "token.h"

using std::make_unique;
using std::move;
using std::string;
using std::function;
using std::unique_ptr;

using namespace ast;

using Factory = function<unique_ptr<Value>(const string &value)>;

/// @brief Builds an AST
class Parser {
 public:
  Token *lookahead;
  Parser(Lexer *lex);
  string parse();

 private:
  Lexer *scanner;
  unordered_map<int, Factory> valueParseMap;
  
  bool Match(int type);
  bool MatchType();
  bool MatchLiteral();

  unique_ptr<Program> parseProgram();
  unique_ptr<Declaration> parseClass();
  unique_ptr<Attribute> parseClassAttribute();
  unique_ptr<Identifier> parseIdentifier();
  unique_ptr<Value> parseValue();
  string parseType();
};
