#pragma once

#include <iostream>
#include <memory>
#include <vector>

using std::stof;
using std::stoi;
using std::move;
using std::string;
using std::vector;
using std::unique_ptr;

namespace ast {
// Abstract Classes
class Node {
 public:
  Node() = default;
  virtual string codegen() = 0;
  virtual ~Node() = default;
};

class Value : public Node {
 public:
  Value() = default;
  virtual string codegen() = 0;
  virtual ~Value() = default;
};

class IntegerLiteral : public Value {
 public:
  IntegerLiteral(string value) : value(stoi(value)) {}
  string codegen() override;

 private:
  int value;
};

class FloatLiteral : public Value {
 public:
  FloatLiteral(string value) : value(stof(value)) {}
  string codegen() override;

 private:
  float value;
};

class CharLiteral : public Value {
 public:
  CharLiteral(string value) : value(value.c_str()[0]) {}
  string codegen() override;

 private:
  char value;
};

class Identifier : public Value {
 public:
  Identifier(string name) : name(name) {};
  string codegen() override;

 private:
  string name;
};

class Attribute : public Node {
 public:
  Attribute(string typeName, unique_ptr<Identifier> attributeName,
            unique_ptr<Value> value)
      : typeName(typeName),
        attributeName(move(attributeName)),
        value(move(value)) {};
  string codegen() override;

 private:
  string typeName;
  unique_ptr<Identifier> attributeName;
  unique_ptr<Value> value;
};

class Declaration : public Node {
 public:
  Declaration(unique_ptr<Identifier> className,
              vector<unique_ptr<Attribute>> classAttributes)
      : className(move(className)), classAttributes(move(classAttributes)) {}
  string codegen() override;

 private:
  unique_ptr<Identifier> className;
  vector<unique_ptr<Attribute>> classAttributes;
};

class Program : public Node {
 public:
  Program(unique_ptr<Declaration> classDeclaration)
      : classDeclaration(move(classDeclaration)) {}
  string codegen() override;

 private:
  unique_ptr<Declaration> classDeclaration;
};

}  // namespace ast