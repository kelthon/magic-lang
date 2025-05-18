#pragma once

#include <iostream>
#include <memory>
#include <vector>

using std::string;
using std::unique_ptr;
using std::vector;

namespace ast {

class Node {
 public:
  Node() = default;
  virtual string codegen() = 0;
  virtual ~Node() = default;
};

class Literal : Node {
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

class Identifier : Node {
 public:
  Identifier(string name) : name(name) {};
  string codegen() override;

 private:
  string name;
};

class Expression : Node {
 public:
  Expression() = default;
  virtual string codegen() override = 0;
};

class AssignmentExpression : Expression {
 public:
  AssignmentExpression(unique_ptr<Identifier> LValue,
                       unique_ptr<Expression> RValue)
      : LValue(move(LValue)), RValue(move(RValue)) {}
  string codegen() override;

 private:
  unique_ptr<Identifier> LValue;
  unique_ptr<Expression> RValue;
};

class Declaration : Node {
 public:
  Declaration(string type, unique_ptr<Identifier> identifier,
              unique_ptr<Expression> initialization)
      : type(type),
        identifier(move(identifier)),
        initialization(move(initialization)) {}
  string codegen() override;

 private:
  string type;
  unique_ptr<Identifier> identifier;
  unique_ptr<Expression> initialization;
};

class Declarations : Node {
 public:
  Declarations(vector<unique_ptr<Declaration>> declarations)
      : declarations(move(declarations)) {}
  string codegen() override;

 private:
  vector<unique_ptr<Declaration>> declarations;
};

class Program : Node {
 public:
  Program(unique_ptr<Declarations> declarations)
      : declarations(move(declarations)) {}
  string codegen() override;

 private:
  unique_ptr<Declarations> declarations;
};

}  // namespace ast