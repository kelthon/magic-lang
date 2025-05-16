#include "parser.h"

#include <memory>

#include "error.h"

using std::make_unique;
using std::move;
using std::unique_ptr;

Parser::Parser(Lexer* lex) {
  scanner = lex;
  lookahead = scanner->scan();
}

bool Parser::Match(int type) {
  if (lookahead->getType() == type) {
    lookahead = scanner->scan();
    return true;
  }

  return false;
}

string Parser::parse() {
  unique_ptr<ASTNode> program = parseProgram();
  return program->codegen();
}

unique_ptr<ProgramNode> Parser::parseProgram() {
  unique_ptr<ASTNode> classDeclaration = parseClassDeclaration();
  return make_unique<ProgramNode>(classDeclaration);
}

unique_ptr<ClassDeclarationNode> Parser::parseClassDeclaration() {
  unique_ptr<ASTNode> header = parseClassDeclarationHeader();
  unique_ptr<ASTNode> className = parseIdentifier();
  unique_ptr<ASTNode> body = parseClassBody();

  unique_ptr<ClassDeclarationNode> classDeclaration =
      make_unique<ClassDeclarationNode>(header, className, body);

  return classDeclaration;
}

unique_ptr<ClassDeclarationHeaderNode> Parser::parseClassDeclarationHeader() {
  if (!Match(TK_TYPE_CLASS)) {
    throw SyntaxError(
        "Invalid syntax: Expected a class token but found an unexpected "
        "element.");
  }

  return make_unique<ClassDeclarationHeaderNode>(lookahead->getLexeme());
}

unique_ptr<IdentifierNode> Parser::parseIdentifier() {
  return make_unique<IdentifierNode>(lookahead->getLexeme());
}

unique_ptr<ClassBodyNode> Parser::parseClassBody() {
  if (!Match('{')) {
    throw SyntaxError(
        "Invalid syntax: Expected '{' before the class body to properly define "
        "the structure.");
  }

  unique_ptr<ASTNode> attributes = parseAttributesDeclaration();
  unique_ptr<ASTNode> constructor = parseConstructorDeclaration();
  unique_ptr<ASTNode> methods = parseMethodsDeclaration();

  unique_ptr<ASTNode> body =
      make_unique<ClassBodyNode>(attributes, constructor, methods);

  if (!Match('}')) {
    throw new SyntaxError(
        "Invalid syntax: Expected '}' to properly close the class body.");
  }

  return body;
}

unique_ptr<AttributesDeclarationNode> Parser::parseAttributesDeclaration() {
  vector<unique_ptr<AttributeDeclarationNode>> attributes = {};

  while (isTypeDeclaration(lookahead)) {
    unique_ptr<AccessModifierNode> accessModifier;
    unique_ptr<ModifierNode> modifiers;
    unique_ptr<DeclarationNode> declaration;

    auto attr = make_unique<AttributeDeclarationNode>(accessModifier, modifiers,
                                                      declaration);

    attributes.push_back((attr));
  }

  // case '(' is a method

  return make_unique<AttributesDeclarationNode>(attributes);
}

unique_ptr<ASTNode> Parser::parseClassMember() {
  /// @todo add class member to grammar
  string accessModifier = "private";
  string modifier = nullptr;
  unique_ptr<ASTNode> classMember;

  // Check if has non access modifiers 'static', 'final', 'abstract'
  if (Match(TK_MODIFIER)) {
    modifier = lookahead->getLexeme();
  }

  // Check if has access modifiers 'private', 'protect', 'public'
  if (Match(TK_ACCESS_MODIFIER)) {
    accessModifier = lookahead->getLexeme();
  }

  if (Match(TK_TYPE_INT)) {
  } else if (Match(TK_TYPE_BOOL)) {
  } else if (Match(TK_TYPE_CHAR)) {
  } else if (Match(TK_TYPE_FLOAT)) {
  } else if (Match(TK_TYPE_DOUBLE)) {
  } else if (Match(TK_TYPE_STRING)) {
  } else {
    throw SyntaxError("Invalid Syntax: Expected a type definition");
  }

  if (!Match(TK_IDENTIFIER)) {
    throw SyntaxError("Invalid Syntax: Expected an Identifier");
  }

  if (Match('(')) {
    classMember = make_unique<MethodDeclarationNode>();

    if (!Match(')')) {
      throw SyntaxError("Invalid Syntax: Missing ')'");
    }
  } else {
    classMember = make_unique<AccessModifierNode>();

    if (!Match(';')) {
      throw SyntaxError("Invalid Syntax: Missing ';' at end of line");
    }
  }

  return classMember;
}

// unique_ptr<ASTNode> Parser::parse() { return; }