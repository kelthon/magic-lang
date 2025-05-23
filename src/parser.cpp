#include "parser.h"

#include <memory>
#include <sstream>
#include <unordered_map>

#include "errors.h"
#include "token.h"

using std::make_unique;
using std::move;
using std::stringstream;
using std::unique_ptr;
using std::unordered_map;

Parser::Parser(Lexer* lex) {
  valueParseMap.emplace(TK_LITERAL_INT,
                        [](const string& value) -> unique_ptr<Value> {
                          return make_unique<IntegerLiteral>(value);
                        });

  valueParseMap.emplace(TK_LITERAL_FLOAT,
                        [](const string& value) -> unique_ptr<Value> {
                          return make_unique<FloatLiteral>(value);
                        });

  valueParseMap.emplace(TK_LITERAL_CHAR,
                        [](const string& value) -> unique_ptr<Value> {
                          return make_unique<CharLiteral>(value);
                        });

  scanner = lex;
}

bool Parser::Match(int type) {
  if (lookahead->getType() == type) {
    lookahead = scanner->scan();
    return true;
  }

  return false;
}

bool Parser::MatchType() {
  if (Token::isType(lookahead->getType())) {
    lookahead = scanner->scan();
    return true;
  }

  return false;
}

bool Parser::MatchLiteral() {
  if (Token::isLiteral(lookahead->getType())) {
    lookahead = scanner->scan();
    return true;
  }

  return false;
}

string Parser::parse() {
  unique_ptr<Program> program = parseProgram();
  return program->codegen();
}

unique_ptr<Program> Parser::parseProgram() {
  unique_ptr<Program> program;
  unique_ptr<Declaration> classDeclaration;

  // Initializing scanner and lookahead
  lookahead = scanner->scan();

  classDeclaration = parseClass();

  program = make_unique<Program>(move(classDeclaration));

  return move(program);
}

unique_ptr<Declaration> Parser::parseClass() {
  unique_ptr<Identifier> className;
  vector<unique_ptr<Attribute>> classAttributes;

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

  // Adding class attributes
  while (Token::isType(lookahead->getType())) {
    unique_ptr<Attribute> attribute = parseClassAttribute();
    classAttributes.push_back(move(attribute));
  }

  return make_unique<Declaration>(move(className), move(classAttributes));
}

unique_ptr<Attribute> Parser::parseClassAttribute() {
  string typeName = parseType();
  unique_ptr<Identifier> attributeName = parseIdentifier();
  unique_ptr<Value> attributeValue;

  if (Match('=')) {
    unique_ptr<Value> attributeValue = parseValue();
  }

  if (!Match(';')) {
    throw SyntaxError("Expected a ';' at end of line.");
  }

  return make_unique<Attribute>(typeName, move(attributeName),
                                move(attributeValue));
}

unique_ptr<Identifier> Parser::parseIdentifier() {
  string identifier = lookahead->getLexeme();

  if (!Match(TK_IDENTIFIER)) {
    throw SyntaxError("Expected a identifier, but found '" +
                      lookahead->getLexeme() + "' instead.");
  }

  return make_unique<Identifier>(identifier);
}

string Parser::parseType() {
  string typeName = lookahead->getLexeme();

  if (!MatchType()) {
    throw SyntaxError("Expected a type name, but found '" +
                      lookahead->getLexeme() + "' instead.");
  }

  return typeName;
}

unique_ptr<Value> Parser::parseValue() {
  int type = lookahead->getType();
  string literal = lookahead->getLexeme();

  if (!MatchLiteral()) {
    throw SyntaxError("Expected a value, but found '" + lookahead->getLexeme() +
                      "' instead.");
  }

  auto iterator = valueParseMap.find(type);

  if(iterator == valueParseMap.end()) {
    throw SyntaxError("Unexpected token '" + literal + "'");
  }

  return iterator->second(literal);
}
