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
  return typeName + " " + attributeName->codegen() + ";";
}

string Attribute::codegen(const string& scope) {
  if (value != nullptr) {
    return scope + attributeName->codegen() + "=" + value->codegen() + ";";
  }

  return "";
}

string Declaration::codegen() {
  stringstream code;
  string classId = "_class_" + className->codegen();

  code << "typedef struct {";

  for (const unique_ptr<Attribute>& attribute : classAttributes) {
    code << attribute->codegen();
  }

  code << "}" + classId + ";";

  // Initialization of all attributes

  code << "int main(int argc,char*argv[]){";
  
  for (const unique_ptr<Attribute>& attribute : classAttributes) {
    code << attribute->codegen(classId + '.');
  }

  code << "return 0;}";

  return code.str();
}

string Program::codegen() { return classDeclaration->codegen(); }