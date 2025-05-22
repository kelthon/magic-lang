#include "ast.h"

#include <iostream>
#include <sstream>

using std::string;
using std::stringstream;
using std::to_string;
using namespace ast;

string Identifier::codegen() { return name; }

string ClassDeclaration::codegen() {
  string cname = className->codegen() + "_class";
  return "typedef struct " + cname + " {} " + cname + ";";
}

string Program::codegen() { return classDeclaration->codegen(); }