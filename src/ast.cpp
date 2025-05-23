#include "ast.h"

#include <iostream>
#include <sstream>

using std::string;
using std::stringstream;
using std::to_string;
using namespace ast;

string IntegerLiteral::codegen() { return to_string(value); }

string FloatLiteral::codegen() { return to_string(value); }

string CharLiteral::codegen() { return to_string(value); }

string Identifier::codegen() { return name; }

string Attribute::codegen() {
  stringstream code;

  code << typeName + " " + attributeName->codegen();

  if (value != nullptr) {
    code << "=" + value->codegen();
  }

  code << ";";

  return code.str();
}

string Declaration::codegen() {
  stringstream code;
  string classId = "_class_" + className->codegen();

  code << "typedef struct {";

  for (const unique_ptr<Attribute>&attribute : classAttributes) {
    code << attribute->codegen();
  }

  code << "}" + classId + ";";

  return code.str();
}

string Program::codegen() { return classDeclaration->codegen(); }