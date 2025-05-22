#include "parser.h"

#include <memory>
#include <sstream>

#include "errors.h"
#include "token.h"

using std::move;
using std::stof;
using std::stoi;
using std::stringstream;
using std::make_unique;
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
  lookahead = scanner->scan();

  if (!Match(TK_TYPE_CLASS)) {
    throw SyntaxError("Expected a class keyword, but found '" +
                      lookahead->getLexeme() + "' instead.");
  }

  if (!Match(TK_IDENTIFIER)) {
    throw SyntaxError("Expected a identifier, but found '" +
                      lookahead->getLexeme() + "' instead.");
  }

  if (!Match('{')) {
    throw SyntaxError("Expected '{', but found '" + lookahead->getLexeme() +
                      "' instead.");
  }
  program = make_unique<Program>(move(parseDeclarations()));

  if (!Match('}')) {
    throw SyntaxError("Expected '}', but found '" + lookahead->getLexeme() +
                      "' instead.");
  }

  return move(program);
}

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

    if (!Match(';')) {
      throw SyntaxError("Expected a ';', but found '" + lookahead->getLexeme() +
                        "' instead.");
    }

    declarations.push_back(make_unique<Declaration>(
        typeName, make_unique<Identifier>(identifierName),
        move(initialization)));
  }

  return make_unique<Declarations>(move(declarations));
}

unique_ptr<Literal> Parser::parseLiteral() {
  switch (lookahead->getType()) {
    case TK_LITERAL_INT:
      return make_unique<IntegerLiteral>(stoi(lookahead->getLexeme()));
    case TK_LITERAL_FLOAT:
      return make_unique<FloatLiteral>(stof(lookahead->getLexeme()));
    case TK_LITERAL_CHAR:
      return make_unique<CharLiteral>(
          lookahead->getLexeme().empty() ? '\0' : lookahead->getLexeme()[0]);

    default:
      return nullptr;
  }
}

unique_ptr<Expression> Parser::parseExpression() {
  unique_ptr<Literal> literal = parseLiteral();
  string lexeme = lookahead->getLexeme();

  if (MatchLiteral()) {
    if (literal == nullptr) {
      throw SyntaxError("Unexpected token '" + lexeme);
    }

    vector<unique_ptr<BinaryFactor>> factors;
    vector<unique_ptr<BinaryTerm>> terms;
    vector<unique_ptr<BinaryComparison>> comparisons;
    vector<unique_ptr<BinaryEquality>> equalities;

    auto unary = make_unique<Unary>(move(literal));
    auto factor = make_unique<Factor>(move(unary), move(factors));
    auto term = make_unique<Term>(move(factor), move(terms));
    auto comparison = make_unique<Comparison>(move(term), move(comparisons));
    auto equality = make_unique<Equality>(move(comparison), move(equalities));

    return move(equality);
  }

  return nullptr;
}
