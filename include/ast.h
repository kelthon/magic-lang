#pragma once

#include <iostream>
#include <memory>
#include <vector>

using std::string;
using std::unique_ptr;
using std::vector;

namespace ast {
// Abstract Classes
class Node {
 public:
  Node() = default;
  virtual string codegen() = 0;
  virtual ~Node() = default;
};

class Identifier : public Node {
 public:
  Identifier(string name) : name(name) {};
  string codegen() override;

 private:
  string name;
};

class ClassDeclaration : public Node {
 public:
  ClassDeclaration(unique_ptr<Identifier> className)
      : className(move(className)) {}
  string codegen() override;

 private:
  unique_ptr<Identifier> className;
};

class Program : public Node {
 public:
  Program(unique_ptr<ClassDeclaration> classDeclaration)
      : classDeclaration(move(classDeclaration)) {}
  string codegen() override;

 private:
  unique_ptr<ClassDeclaration> classDeclaration;
};

}  // namespace ast