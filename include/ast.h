#pragma once

#include <iostream>
#include <memory>
#include <vector>

using std::string;
using std::unique_ptr;
using std::vector;

namespace ast {

class Expression {
 public:
  Expression() = default;
  virtual string codegen() = 0;
  virtual ~Expression() = default;
};

class Literal : Expression {
 public:
  Literal() = default;
  string codegen() override = 0;
};

class IntegerLiteral : Literal {
 public:
  IntegerLiteral(int value) : value(value) {}
  string codegen() override;

 private:
  int value;
};

class FloatLiteral : Literal {
 public:
  FloatLiteral(float value) : value(value) {}
  string codegen() override;

 private:
  float value;
};

class CharLiteral : Literal {
 public:
  CharLiteral(char value) : value(value) {}
  string codegen() override;

 private:
  char value;
};

class Identifier : Expression {
 public:
  Identifier(string name) : name(name) {};
  string codegen() override;

 private:
  string name;
};

class Declaration : Expression {
 public:
  Declaration(string type, unique_ptr<Identifier> identifier)
      : type(type), identifier(move(identifier)) {}
  string codegen() override;

 private:
  string type;
  unique_ptr<Identifier> identifier;
};

class Declarations : Expression {
 public:
  Declarations(vector<unique_ptr<Declaration>> declarations)
      : declarations(move(declarations)) {}
  string codegen() override;

 private:
  vector<unique_ptr<Declaration>> declarations;
};

class Program : Expression {
 public:
  Program(unique_ptr<Declarations> declarations)
      : declarations(move(declarations)) {}
  string codegen() override;

 private:
  unique_ptr<Declarations> declarations;
};

}  // namespace ast