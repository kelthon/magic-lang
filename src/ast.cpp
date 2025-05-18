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

string Declaration::codegen() { return type + " " + identifier->codegen() + ";"; }

string Declarations::codegen() {
  stringstream code;

  for (const unique_ptr<Declaration> &decl : declarations) {
    code << decl->codegen();
  }

  return code.str();
}
string Program::codegen() { return declarations->codegen(); }