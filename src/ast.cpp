#include "ast.h"

#include <iostream>
#include <sstream>

using std::string;
using std::stringstream;
using std::to_string;
using namespace ast;

string IntegerLiteral::codegen() { return to_string(value); }

string FloatLiteral::codegen() { return to_string(value); }

string CharLiteral::codegen() { return string(1, value); }

string Identifier::codegen() { return name; }

string Unary::codegen() { return primary->codegen(); }

string BinaryFactor::codegen() {
  return operatorSymbol + " " + unary->codegen();
}

string Factor::codegen() {
  stringstream code;

  code << unary->codegen();

  for (const std::unique_ptr<ast::BinaryFactor> &factor : binaryFactor) {
    code << " " + factor->codegen();
  }

  return code.str();
}

string BinaryTerm::codegen() {
  return operatorSymbol + " " + factor->codegen();
}

string Term::codegen() {
  stringstream code;

  code << factor->codegen();

  for (const std::unique_ptr<ast::BinaryTerm> &term : binaryTerm) {
    code << " " + term->codegen();
  }

  return code.str();
}

string BinaryComparison::codegen() {
  return operatorSymbol + " " + term->codegen();
}

string Comparison::codegen() {
  stringstream code;

  code << term->codegen();

  for (const std::unique_ptr<ast::BinaryComparison> &comparison : binaryComparison) {
    code << " " + comparison->codegen();
  }

  return code.str();
}

string BinaryEquality::codegen() {
  return operatorSymbol + " " + comparison->codegen();
}

string Equality::codegen() {
  stringstream code;

  code << comparison->codegen();

  for (const std::unique_ptr<ast::BinaryEquality> &equality : binaryEquality) {
    code << " " + equality->codegen();
  }

  return code.str();
}

string Assignment::codegen() {
  return LValue->codegen() + "=" + RValue->codegen();
}

string Declaration::codegen() {
  stringstream code;

  code << type + " " + identifier->codegen();

  if (initialization != nullptr) {
    code << initialization->codegen();
  }

  code << ';';

  return code.str();
}

string Declarations::codegen() {
  stringstream code;

  for (const unique_ptr<Declaration> &decl : declarations) {
    code << decl->codegen();
  }

  return code.str();
}
string Program::codegen() { return declarations->codegen(); }