#pragma once

#include <iostream>
#include <memory>

#include "ast.h"
#include "lexer.h"
#include "token.h"

using std::make_unique;
using std::move;
using std::string;
using std::unique_ptr;

using namespace ast;

/// @brief Builds an AST
class Parser {
 public:
  Token *lookahead;
  Parser(Lexer *lex);
  string parse();

 private:
  Lexer *scanner;
  bool Match(int type);
  bool MatchType();
  bool MatchLiteral();

  unique_ptr<Program> parseProgram();
  unique_ptr<ClassDeclaration> parseClass();
  unique_ptr<Identifier> parseIdentifier();
};
