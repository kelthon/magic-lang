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

class Primary : public Node {
 public:
  Primary() = default;
  virtual string codegen() = 0;
  virtual ~Primary() = default;
};

class Literal : public Primary {
 public:
  Literal() = default;
  virtual string codegen() = 0;
  virtual ~Literal() = default;
};

class Expression : public Primary {
 public:
  Expression() = default;
  virtual string codegen() override = 0;
  virtual ~Expression() = default;
};

// Concrete Classes
class IntegerLiteral : public Literal {
 public:
  IntegerLiteral(int value) : value(value) {}
  string codegen() override;

 private:
  int value;
};

class FloatLiteral : public Literal {
 public:
  FloatLiteral(float value) : value(value) {}
  string codegen() override;

 private:
  float value;
};

class CharLiteral : public Literal {
 public:
  CharLiteral(char value) : value(value) {}
  string codegen() override;

 private:
  char value;
};

class Identifier : public Primary {
 public:
  Identifier(string name) : name(name) {};
  string codegen() override;

 private:
  string name;
};

class Unary : public Expression {
 public:
  Unary(unique_ptr<Primary> primary) : primary(move(primary)) {}
  string codegen() override;

 private:
  unique_ptr<Primary> primary;
};

class BinaryFactor : public Expression {
 public:
  BinaryFactor(string operatorSymbol, unique_ptr<Unary> unary)
      : operatorSymbol(operatorSymbol), unary(move(unary)) {}

  string codegen() override;

 private:
  string operatorSymbol;
  unique_ptr<Unary> unary;
};

class Factor : public Expression {
 public:
  Factor(unique_ptr<Unary> unary, vector<unique_ptr<BinaryFactor>> binaryFactor)
      : unary(move(unary)), binaryFactor(move(binaryFactor)) {}

  string codegen() override;

 private:
  unique_ptr<Unary> unary;
  vector<unique_ptr<BinaryFactor>> binaryFactor;
};

class BinaryTerm : public Expression {
 public:
  BinaryTerm(string operatorSymbol, unique_ptr<Factor> factor)
      : operatorSymbol(operatorSymbol), factor(move(factor)) {}

  string codegen() override;

 private:
  string operatorSymbol;
  unique_ptr<Factor> factor;
};

class Term : public Expression {
 public:
  Term(unique_ptr<Factor> factor, vector<unique_ptr<BinaryTerm>> binaryTerm)
      : factor(move(factor)), binaryTerm(move(binaryTerm)) {}

  string codegen() override;

 private:
  unique_ptr<Factor> factor;
  vector<unique_ptr<BinaryTerm>> binaryTerm;
};

class BinaryComparison : public Expression {
 public:
  BinaryComparison(string operatorSymbol, unique_ptr<Term> term)
      : operatorSymbol(operatorSymbol), term(move(term)) {}

  string codegen() override;

 private:
  string operatorSymbol;
  unique_ptr<Term> term;
};

class Comparison : public Expression {
 public:
  Comparison(unique_ptr<Term> term,
             vector<unique_ptr<BinaryComparison>> binaryComparison)
      : term(move(term)), binaryComparison(move(binaryComparison)) {}
  string codegen() override;

 private:
  vector<unique_ptr<BinaryComparison>> binaryComparison;
  unique_ptr<Term> term;
};

class BinaryEquality : public Expression {
 public:
  BinaryEquality(string operatorSymbol, unique_ptr<Comparison> comparison)
      : operatorSymbol(operatorSymbol), comparison(move(comparison)) {}
  string codegen() override;

 private:
  string operatorSymbol;
  unique_ptr<Comparison> comparison;
};

class Equality : public Expression {
 public:
  Equality(unique_ptr<Comparison> comparison,
           vector<unique_ptr<BinaryEquality>> binaryEquality)
      : comparison(move(comparison)), binaryEquality(move(binaryEquality)) {}
  string codegen() override;

 private:
  unique_ptr<Comparison> comparison;
  vector<unique_ptr<BinaryEquality>> binaryEquality;
};

class Assignment : public Expression {
 public:
  Assignment(unique_ptr<Identifier> LValue, unique_ptr<Expression> RValue)
      : LValue(move(LValue)), RValue(move(RValue)) {}
  string codegen() override;

 private:
  unique_ptr<Identifier> LValue;
  unique_ptr<Expression> RValue;
};

class Declaration : public Node {
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

class Declarations : public Node {
 public:
  Declarations(vector<unique_ptr<Declaration>> declarations)
      : declarations(move(declarations)) {}
  string codegen() override;

 private:
  vector<unique_ptr<Declaration>> declarations;
};

class Program : public Node {
 public:
  Program(unique_ptr<Declarations> declarations)
      : declarations(move(declarations)) {}
  string codegen() override;

 private:
  unique_ptr<Declarations> declarations;
};

}  // namespace ast