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

  unique_ptr<ProgramNode> parseProgram();
  unique_ptr<ClassDeclarationNode> parseClassDeclaration();
  unique_ptr<ClassDeclarationHeaderNode> parseClassDeclarationHeader();
  unique_ptr<IdentifierNode> parseIdentifier();
  unique_ptr<ClassBodyNode> parseClassBody();
  unique_ptr<AttributesDeclarationNode> parseAttributesDeclaration();
  unique_ptr<ASTNode> parseClassMember();
  unique_ptr<ASTNode> parseConstructorDeclaration();
  unique_ptr<ASTNode> parseMethodsDeclaration();
};
