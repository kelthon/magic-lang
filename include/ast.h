#pragma once

#include <iostream>
#include <memory>
#include <vector>

using std::string;
using std::unique_ptr;
using std::vector;

namespace ast {

class ASTNode {
 public:
  ASTNode() = default;
  virtual string codegen() = 0;
};

class ExpressionNode;

class BlockNode;

class StatementWithoutReturnNode;

class IdentifierNode : public ASTNode {
 public:
  IdentifierNode(string name) : name(name) {};
  string codegen() override;

 private:
  string name;
};

class TypeNode : public ASTNode {
 public:
  TypeNode(string typeName) : typeName(typeName) {}
  string codegen() override;

 private:
  string typeName;
};

class TermOperatorNode : public ASTNode {
 public:
  TermOperatorNode(string op) : op(op) {};
  string codegen() override;

 private:
  string op;
};

class FactorOperatorNode : public ASTNode {
 public:
  FactorOperatorNode(string op) : op(op) {};
  string codegen() override;

 private:
  string op;
};

class AssignmentExpressionNode : public ASTNode {
 public:
  AssignmentExpressionNode(unique_ptr<IdentifierNode> left,
                           unique_ptr<ExpressionNode> right)
      : left(move(left)), right(move(right)) {};
  string codegen() override;

 private:
  unique_ptr<IdentifierNode> left;
  unique_ptr<ExpressionNode> right;
};

class PriorityExpressionNode : public ASTNode {
 public:
  PriorityExpressionNode(unique_ptr<ExpressionNode> expression)
      : expression(move(expression)) {};
  string codegen() override;

 private:
  unique_ptr<ExpressionNode> expression;
};

class AdditionExpressionNode : public ASTNode {
 public:
  AdditionExpressionNode(unique_ptr<ExpressionNode> left,
                         unique_ptr<TermOperatorNode> op,
                         unique_ptr<ExpressionNode> right)
      : left(move(left)), op(move(op)), right(move(right)) {};
  string codegen() override;

 private:
  unique_ptr<ExpressionNode> left;
  unique_ptr<ExpressionNode> right;
  unique_ptr<TermOperatorNode> op;
};

class MultiplicationExpressionNode : public ASTNode {
 public:
  MultiplicationExpressionNode(unique_ptr<ExpressionNode> left,
                               unique_ptr<FactorOperatorNode> op,
                               unique_ptr<ExpressionNode> right)
      : left(move(left)), op(move(op)), right(move(right)) {};
  string codegen() override;

 private:
  unique_ptr<ExpressionNode> left;
  unique_ptr<ExpressionNode> right;
  unique_ptr<FactorOperatorNode> op;
};

class RelationalExpressionNode : public ASTNode {
 public:
  RelationalExpressionNode(unique_ptr<ExpressionNode> left,
                           unique_ptr<ExpressionNode> right)
      : left(move(left)), right(move(right)) {};
  string codegen() override;

 private:
  unique_ptr<ExpressionNode> left;
  unique_ptr<ExpressionNode> right;
};

class ParameterNode : public ASTNode {
 public:
  ParameterNode(unique_ptr<IdentifierNode> type,
                unique_ptr<IdentifierNode> name)
      : type(move(type)), name(move(name)) {};
  string codegen() override;

 private:
  unique_ptr<IdentifierNode> type;
  unique_ptr<IdentifierNode> name;
};

class ParametersNode : public ASTNode {
 public:
  ParametersNode(vector<unique_ptr<ParameterNode>> parameters)
      : parameters(move(parameters)) {};
  string codegen() override;

 private:
  vector<unique_ptr<ParameterNode>> parameters;
};

class AccessModifierNode : public ASTNode {
 public:
  AccessModifierNode(string modifier) : modifier(modifier) {};
  string codegen() override;

 private:
  string modifier;
};

class ModifierNode : public ASTNode {
 public:
  ModifierNode(string modifier) : modifier(modifier) {};
  string codegen() override;

 private:
  string modifier;
};

class ObjectInstanceExpressionNode : public ASTNode {
 public:
  ObjectInstanceExpressionNode(unique_ptr<IdentifierNode> name)
      : name(move(name)) {};
  string codegen() override;

 private:
  unique_ptr<IdentifierNode> name;
};

class MemberAccessExpressionNode : public ASTNode {
 public:
  MemberAccessExpressionNode(unique_ptr<IdentifierNode> memberName,
                             unique_ptr<ObjectInstanceExpressionNode> instance)
      : memberName(move(memberName)), instance(move(instance)) {};
  string codegen() override;

 private:
  unique_ptr<IdentifierNode> memberName;
  unique_ptr<ObjectInstanceExpressionNode> instance;
};

class MethodCallExpressionNode : public ASTNode {
 public:
  MethodCallExpressionNode(unique_ptr<IdentifierNode> methodName,
                           unique_ptr<ObjectInstanceExpressionNode> instance)
      : methodName(move(methodName)), instance(move(instance)) {};
  string codegen() override;

 private:
  unique_ptr<IdentifierNode> methodName;
  unique_ptr<ObjectInstanceExpressionNode> instance;
};

class ExpressionNode : ASTNode {
 public:
  ExpressionNode(
      unique_ptr<AssignmentExpressionNode> assignmentExpression,
      unique_ptr<AdditionExpressionNode> additionExpression,
      unique_ptr<MultiplicationExpressionNode> multiplicationExpression,
      unique_ptr<PriorityExpressionNode> priorityExpression,
      unique_ptr<RelationalExpressionNode> relationalExpression,
      unique_ptr<MethodCallExpressionNode> methodCallExpression,
      unique_ptr<MemberAccessExpressionNode> memberAccessExpression,
      unique_ptr<ObjectInstanceExpressionNode> instance)
      : assignmentExpression(move(assignmentExpression)),
        additionExpression(move(additionExpression)),
        multiplicationExpression(move(multiplicationExpression)),
        priorityExpression(move(priorityExpression)),
        relationalExpression(move(relationalExpression)),
        methodCallExpression(move(methodCallExpression)),
        memberAccessExpression(move(memberAccessExpression)),
        instance(move(instance)) {};
  string codegen() = 0;

 private:
  unique_ptr<AssignmentExpressionNode> assignmentExpression;
  unique_ptr<AdditionExpressionNode> additionExpression;
  unique_ptr<MultiplicationExpressionNode> multiplicationExpression;
  unique_ptr<PriorityExpressionNode> priorityExpression;
  unique_ptr<RelationalExpressionNode> relationalExpression;
  unique_ptr<MethodCallExpressionNode> methodCallExpression;
  unique_ptr<MemberAccessExpressionNode> memberAccessExpression;
  unique_ptr<ObjectInstanceExpressionNode> instance;
};

class ExpressionsNode : public ASTNode {
 public:
  ExpressionsNode(vector<unique_ptr<ExpressionNode>> expressions)
      : expressions(move(expressions)) {};
  string codegen() = 0;

 private:
  vector<unique_ptr<ExpressionNode>> expressions;
};

class IfStatementNode : public ASTNode {
 public:
  IfStatementNode(unique_ptr<RelationalExpressionNode> condition,
                  unique_ptr<BlockNode> ifBlock)
      : condition(move(condition)), ifBlock(move(ifBlock)) {};
  string codegen() override;

 private:
  unique_ptr<RelationalExpressionNode> condition;
  unique_ptr<BlockNode> ifBlock;
};

class ElseStatementNode : public ASTNode {
 public:
  ElseStatementNode(unique_ptr<BlockNode> elseBlock)
      : elseBlock(move(elseBlock)) {};
  string codegen() override;

 private:
  unique_ptr<BlockNode> elseBlock;
};

class IfElseStatementNode : public ASTNode {
 public:
  IfElseStatementNode(unique_ptr<RelationalExpressionNode> condition,
                      unique_ptr<IfStatementNode> ifBlock,
                      unique_ptr<ElseStatementNode> elseBlock)
      : condition(move(condition)),
        ifBlock(move(ifBlock)),
        elseBlock(move(elseBlock)) {};

  string codegen() override;

 private:
  unique_ptr<RelationalExpressionNode> condition;
  unique_ptr<IfStatementNode> ifBlock;
  unique_ptr<ElseStatementNode> elseBlock;
};

class WhileStatementNode : public ASTNode {
 public:
  WhileStatementNode(unique_ptr<RelationalExpressionNode> condition,
                     unique_ptr<BlockNode> whileBlock)
      : condition(move(condition)), whileBlock(move(whileBlock)) {};
  string codegen() override;

 private:
  unique_ptr<RelationalExpressionNode> condition;
  unique_ptr<BlockNode> whileBlock;
};

class ForInitializationNode : public ASTNode {
 public:
  ForInitializationNode(unique_ptr<IdentifierNode> iteratorType,
                        unique_ptr<IdentifierNode> iteratorName,
                        unique_ptr<ExpressionsNode> expressions)
      : iteratorType(move(iteratorType)),
        iteratorName(move(iteratorName)),
        expressions(move(expressions)) {};
  string codegen() override;

 private:
  unique_ptr<IdentifierNode> iteratorType;
  unique_ptr<IdentifierNode> iteratorName;
  unique_ptr<ExpressionsNode> expressions;
};

class ForIncrementNode : public ASTNode {
 public:
  ForIncrementNode(unique_ptr<IdentifierNode> iteratorName,
                   unique_ptr<AssignmentExpressionNode> increment)
      : iteratorName(move(iteratorName)), increment(move(increment)) {};
  string codegen() override;

 private:
  unique_ptr<IdentifierNode> iteratorName;
  unique_ptr<AssignmentExpressionNode> increment;
};

class ForParametersNode : public ASTNode {
 public:
  ForParametersNode(unique_ptr<ForInitializationNode> initialization,
                    unique_ptr<RelationalExpressionNode> condition,
                    unique_ptr<ForIncrementNode> increment)
      : initialization(move(initialization)),
        condition(move(condition)),
        increment(move(increment)) {};
  string codegen() override;

 private:
  unique_ptr<ForInitializationNode> initialization;
  unique_ptr<RelationalExpressionNode> condition;
  unique_ptr<ForIncrementNode> increment;
};

class ForStatementNode : public ASTNode {
 public:
  ForStatementNode(unique_ptr<ForParametersNode> parameters,
                   unique_ptr<BlockNode> forBlock)
      : parameters(move(parameters)), forBlock(move(forBlock)) {};
  string codegen() override;

 private:
  unique_ptr<ForParametersNode> parameters;
  unique_ptr<BlockNode> forBlock;
};

class ReturnStatement : public ASTNode {
 public:
  ReturnStatement(unique_ptr<ExpressionsNode> expressions)
      : expressions(move(expressions)) {};
  string codegen() override;

 private:
  unique_ptr<ExpressionsNode> expressions;
};

class StatementWithoutReturnNode : public ASTNode {
 public:
  StatementWithoutReturnNode(unique_ptr<IfElseStatementNode> ifElseStatement,
                             unique_ptr<WhileStatementNode> whileStatement,
                             unique_ptr<ForStatementNode> forStatement,
                             unique_ptr<ExpressionsNode> expressions)
      : ifElseStatement(move(ifElseStatement)),
        whileStatement(move(whileStatement)),
        forStatement(move(forStatement)),
        expressions(move(expressions)) {};
  string codegen() override;

 private:
  unique_ptr<IfElseStatementNode> ifElseStatement;
  unique_ptr<WhileStatementNode> whileStatement;
  unique_ptr<ForStatementNode> forStatement;
  unique_ptr<ExpressionsNode> expressions;
};

class StatementNode : ASTNode {
 public:
  StatementNode(unique_ptr<StatementWithoutReturnNode> statement,
                unique_ptr<ReturnStatement> returnStatement)
      : statement(move(statement)), returnStatement(move(returnStatement)) {};
  string codegen() override;

 private:
  unique_ptr<StatementWithoutReturnNode> statement;
  unique_ptr<ReturnStatement> returnStatement;
};

class StatementsNode : public ASTNode {
 public:
  StatementsNode(vector<unique_ptr<StatementNode>> statements)
      : statements(move(statements)) {};
  string codegen() = 0;

 private:
  vector<unique_ptr<StatementNode>> statements;
};

class BlockNode : public ASTNode {
 public:
  BlockNode(vector<unique_ptr<StatementsNode>> statements)
      : statements(move(statements)) {};
  string codegen() override;

 private:
  vector<unique_ptr<StatementsNode>> statements;
};

class InitializationNode : public ASTNode {
 public:
  InitializationNode(unique_ptr<ExpressionsNode> expressions)
      : expressions(move(expressions)) {};
  string codegen() override;

 private:
  unique_ptr<ExpressionsNode> expressions;
};

class DeclarationNode : public ASTNode {
 public:
  DeclarationNode(unique_ptr<IdentifierNode> type,
                  unique_ptr<IdentifierNode> name,
                  unique_ptr<InitializationNode> initialization)
      : type(move(type)),
        name(move(name)),
        initialization(move(initialization)) {};
  string codegen() override;

 private:
  unique_ptr<IdentifierNode> type;
  unique_ptr<IdentifierNode> name;
  unique_ptr<InitializationNode> initialization;
};

class AttributeDeclarationNode : public ASTNode {
 public:
  AttributeDeclarationNode(unique_ptr<AccessModifierNode> accessModifier,
                           vector<unique_ptr<ModifierNode>> modifiers,
                           unique_ptr<DeclarationNode> declaration)
      : accessModifier(move(accessModifier)),
        modifiers(move(modifiers)),
        declaration(move(declaration)) {};
  string codegen() override;

 private:
  unique_ptr<AccessModifierNode> accessModifier;
  vector<unique_ptr<ModifierNode>> modifiers;
  unique_ptr<DeclarationNode> declaration;
};

class AttributesDeclarationNode : public ASTNode {
 public:
  AttributesDeclarationNode(
      vector<unique_ptr<AttributeDeclarationNode>> attributes)
      : attributes(move(attributes)) {};
  string codegen() override;

 private:
  vector<unique_ptr<AttributeDeclarationNode>> attributes;
};

class ConstructorStatementsNode : public ASTNode {
 public:
  ConstructorStatementsNode(
      vector<unique_ptr<StatementWithoutReturnNode>> statements)
      : statements(move(statements)) {};
  string codegen() override;

 private:
  vector<unique_ptr<StatementWithoutReturnNode>> statements;
};

class ConstructorSignatureNode : public ASTNode {
 public:
  ConstructorSignatureNode(unique_ptr<IdentifierNode> className,
                           unique_ptr<ParametersNode> parameters)
      : className(move(className)), parameters(move(parameters)) {};
  string codegen() override;

 private:
  unique_ptr<IdentifierNode> className;
  unique_ptr<ParametersNode> parameters;
};

class ConstructorBodyNode : public ASTNode {
 public:
  ConstructorBodyNode(unique_ptr<ConstructorStatementsNode> statements)
      : statements(move(statements)) {};
  string codegen() override;

 private:
  unique_ptr<ConstructorStatementsNode> statements;
};

class ConstructorDeclarationNode : public ASTNode {
 public:
  ConstructorDeclarationNode(unique_ptr<ConstructorSignatureNode> signature,
                             unique_ptr<ConstructorBodyNode> body)
      : signature(move(signature)), body(move(body)) {};
  string codegen() override;

 private:
  unique_ptr<ConstructorSignatureNode> signature;
  unique_ptr<ConstructorBodyNode> body;
};

class MethodSignatureNode : public ASTNode {
 public:
  MethodSignatureNode(unique_ptr<AccessModifierNode> accessModifier,
                      vector<unique_ptr<ModifierNode>> modifiers,
                      unique_ptr<IdentifierNode> returnType,
                      unique_ptr<IdentifierNode> methodName,
                      unique_ptr<ParametersNode> parameters)
      : accessModifier(move(accessModifier)),
        modifiers(move(modifiers)),
        methodName(move(methodName)),
        returnType(move(returnType)),
        parameters(move(parameters)) {};
  string codegen() override;

 private:
  unique_ptr<AccessModifierNode> accessModifier;
  vector<unique_ptr<ModifierNode>> modifiers;
  unique_ptr<IdentifierNode> returnType;
  unique_ptr<IdentifierNode> methodName;
  unique_ptr<ParametersNode> parameters;
};

class MethodBodyNode : public ASTNode {
 public:
  MethodBodyNode(vector<unique_ptr<StatementsNode>> statements)
      : statements(move(statements)) {};
  string codegen() override;

 private:
  vector<unique_ptr<StatementsNode>> statements;
};

class MethodDeclarationNode : public ASTNode {
 public:
  MethodDeclarationNode(unique_ptr<MethodSignatureNode> signature,
                        unique_ptr<MethodBodyNode> body)
      : signature(move(signature)), body(move(body)) {};
  string codegen() override;

 private:
  unique_ptr<MethodSignatureNode> signature;
  unique_ptr<MethodBodyNode> body;
};

class MethodsDeclarationNode : public ASTNode {
 public:
  MethodsDeclarationNode(vector<unique_ptr<MethodDeclarationNode>> methods)
      : methods(move(methods)) {};
  string codegen() override;

 private:
  vector<unique_ptr<MethodDeclarationNode>> methods;
};

class ClassBodyNode : public ASTNode {
 public:
  ClassBodyNode(unique_ptr<AttributesDeclarationNode> attributes,
                unique_ptr<ConstructorDeclarationNode> constructor,
                unique_ptr<MethodsDeclarationNode> methods)
      : attributes(move(attributes)),
        constructor(move(constructor)),
        methods(move(methods)) {};
  string codegen() override;

 private:
  unique_ptr<AttributesDeclarationNode> attributes;
  unique_ptr<ConstructorDeclarationNode> constructor;
  unique_ptr<MethodsDeclarationNode> methods;
};

class ClassDeclarationHeaderNode : public ASTNode {
 public:
  ClassDeclarationHeaderNode(string header) : header(header) {};
  string codegen() override;

 private:
  string header;
};

class ClassDeclarationNode : public ASTNode {
 public:
  ClassDeclarationNode(unique_ptr<ClassDeclarationHeaderNode> header,
                       unique_ptr<IdentifierNode> className,
                       unique_ptr<ClassBodyNode> body)
      : header(move(header)), className(move(className)), body(move(body)) {};
  string codegen() override;

 private:
  unique_ptr<ClassDeclarationHeaderNode> header;
  unique_ptr<IdentifierNode> className;
  unique_ptr<ClassBodyNode> body;
};

class ProgramNode : public ASTNode {
 public:
  ProgramNode(unique_ptr<ClassDeclarationNode> classDeclaration)
      : classDeclaration(move(classDeclaration)) {};
  string codegen() override;

 private:
  unique_ptr<ClassDeclarationNode> classDeclaration;
};
}  // namespace ast