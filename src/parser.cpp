#include "parser.h"

#include <memory>
#include <sstream>

#include "errors.h"
#include "token.h"

using std::make_unique;
using std::move;
using std::stof;
using std::stoi;
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

bool Parser::MatchLiteral() {
  switch (lookahead->getType()) {
    case TK_LITERAL_INT:
    case TK_LITERAL_BOOL:
    case TK_LITERAL_CHAR:
    case TK_LITERAL_FLOAT:
    case TK_LITERAL_DOUBLE:
    case TK_LITERAL_STRING:
    case TK_LITERAL_CLASS:
    case TK_LITERAL_NULL:
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
  unique_ptr<Program> program;
  unique_ptr<ClassDeclaration> classDeclaration;

  // Initializing scanner and lookahead
  lookahead = scanner->scan();

  classDeclaration = parseClass();

  program = make_unique<Program>(move(classDeclaration));

  return move(program);
}

unique_ptr<ClassDeclaration> Parser::parseClass() {
  unique_ptr<Identifier> className;

  // Checking if is missing class token
  if (!Match(TK_TYPE_CLASS)) {
    throw SyntaxError("Expected 'class' keyword, but found '" +
                      lookahead->getLexeme() + "' instead.");
  }

  // Checking if is missing class identifier
  className = parseIdentifier();

  // Checking if is missing a block start token
  if (!Match('{')) {
    throw SyntaxError("Expected '{', but found '" + lookahead->getLexeme() +
                      "' instead.");
  }

  return make_unique<ClassDeclaration>(move(className));
}

unique_ptr<Identifier> Parser::parseIdentifier() {
  string identifier = lookahead->getLexeme();

  if (!Match(TK_IDENTIFIER)) {
    throw SyntaxError("Expected a identifier, but found '" +
                      lookahead->getLexeme() + "' instead.");
  }

  return make_unique<Identifier>(identifier);
}
