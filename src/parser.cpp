#include "parser.h"

#include <memory>
#include <sstream>

#include "error.h"
#include "token.h"

using std::make_unique;
using std::move;
using std::stringstream;
using std::unique_ptr;

Parser::Parser(Lexer* lex) { scanner = lex; }

bool Parser::Match(int type) {
  if (lookahead->getType() == type) {
    lookahead = scanner->scan();
    return true;
  }

  return false;
}

bool Parser::MatchType() {
  switch (lookahead->getType()) {
    case TK_TYPE_INT:
    case TK_TYPE_BOOL:
    case TK_TYPE_CHAR:
    case TK_TYPE_FLOAT:
    case TK_TYPE_DOUBLE:
    case TK_TYPE_STRING:
      lookahead = scanner->scan();
      return true;

    default:
      return false;
  }
}

string Parser::parse() {
  unique_ptr<Program> program = parseProgram();

  return program->codegen();
}

unique_ptr<Program> Parser::parseProgram() {
  lookahead = scanner->scan();
  return make_unique<Program>(move(parseDeclarations()));
}

void Parser::parseIdentifier() {}

unique_ptr<Declarations> Parser::parseDeclarations() {
  string typeName, identifierName;
  unique_ptr<Expression> initialization = nullptr;
  vector<unique_ptr<Declaration>> declarations;

  while (lookahead != nullptr && !scanner->end()) {
    typeName = lookahead->getLexeme();

    if (!MatchType()) {
      throw SyntaxError("Expected a type name, but found '" +
                        lookahead->getLexeme() + "' instead.");
    }

    identifierName = lookahead->getLexeme();

    if (!Match(TK_IDENTIFIER)) {
      throw SyntaxError("Expected a identifier, but found '" +
                        lookahead->getLexeme() + "' instead.");
    }

    if (Match('=')) {
      initialization = parseExpression();
    }

    if(!Match(';')) {
      throw SyntaxError("Expected a ';', but found '" +
                        lookahead->getLexeme() + "' instead.");
    }

    declarations.push_back(make_unique<Declaration>(
        typeName, make_unique<Identifier>(identifierName), initialization));
  }

  return make_unique<Declarations>(move(declarations));
}

unique_ptr<Expression> Parser::parseExpression() {
  
}
