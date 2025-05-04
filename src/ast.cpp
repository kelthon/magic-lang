#include "ast.h"

#include <iostream>

using std::string;

namespace ast {
string IdentifierNode::codegen() { return name; }

string TypeNode::codegen() { return typeName; }

string TermOperatorNode::codegen() { return op; }

string FactorOperatorNode::codegen() { return op; }

string AssignmentExpressionNode::codegen() {
  return left->codegen() + right->codegen();
}

string PriorityExpressionNode::codegen() {
  return "(" + expression->codegen() + ")";
}

string AdditionExpressionNode::codegen() {
  return left->codegen() + op->codegen() + right->codegen();
}

string MultiplicationExpressionNode::codegen() {
  return left->codegen() + op->codegen() + right->codegen();
}

string RelationalExpressionNode::codegen() {
  return left->codegen() + right->codegen();
}

string ParameterNode::codegen() {
  return type->codegen() + " " + name->codegen();
}

string ParametersNode::codegen() {
  int i = 0;
  string code = "";

  for (const unique_ptr<ParameterNode>& parameter : parameters) {
    code = code + parameter->codegen();

    if (i < parameters.size()) {
      code = code + ", ";
    }

    i++;
  }

  return code;
}

string AccessModifierNode::codegen() { return modifier; }

string ModifierNode::codegen() { return modifier; }

string ObjectInstanceExpressionNode::codegen() { return name->codegen(); }

string MemberAccessExpressionNode::codegen() {
  return instance->codegen() + "." + memberName->codegen();
}

string MethodCallExpressionNode::codegen() {
  return methodName->codegen() + "(" + instance->codegen() + ")";
}

string ExpressionNode::codegen() {
  if (assignmentExpression) {
    return assignmentExpression->codegen();
  }

  if (additionExpression) {
    return additionExpression->codegen();
  }

  if (multiplicationExpression) {
    return multiplicationExpression->codegen();
  }

  if (priorityExpression) {
    return priorityExpression->codegen();
  }

  if (relationalExpression) {
    return relationalExpression->codegen();
  }

  if (methodCallExpression) {
    return methodCallExpression->codegen();
  }

  if (memberAccessExpression) {
    return memberAccessExpression->codegen();
  }

  if (instance) {
    return instance->codegen();
  }

  return "";
}

string ExpressionsNode::codegen() {
  string code = "";
  for (const unique_ptr<ExpressionNode>& expr : expressions) {
    code = code + expr->codegen();
  }

  return code;
}

string IfStatementNode::codegen() {
  return condition->codegen() + ifBlock->codegen();
}

string ElseStatementNode::codegen() { return elseBlock->codegen(); }

string IfElseStatementNode::codegen() {
  string code = ifBlock->codegen();

  if (elseBlock) {
    code = code + elseBlock->codegen();
  }

  return code;
}

string WhileStatementNode::codegen() {
  return condition->codegen() + whileBlock->codegen();
}

string ForInitializationNode::codegen() {
  string code = iteratorType->codegen() + " " + iteratorName->codegen();

  if (expressions) {
    code = code + expressions->codegen();
  }

  return code;
}

string ForIncrementNode::codegen() {
  return iteratorName->codegen() + increment->codegen();
}

string ForParametersNode::codegen() {
  return initialization->codegen() + ";" + condition->codegen() + ";" +
         increment->codegen();
}

string ForStatementNode::codegen() {
  return parameters->codegen() + forBlock->codegen();
}

string ReturnStatement::codegen() { return expressions->codegen(); }

string StatementWithoutReturnNode::codegen() {
  if (ifElseStatement) {
    return ifElseStatement->codegen();
  }

  if (whileStatement) {
    return whileStatement->codegen();
  }

  if (forStatement) {
    return forStatement->codegen();
  }

  if (expressions) {
    return expressions->codegen();
  }

  return "";
}

string StatementNode::codegen() {
  string code = "";

  if (statement) {
    code = code + statement->codegen();
  }

  if (returnStatement) {
    code = code + returnStatement->codegen();
  }

  return code;
}

string StatementsNode::codegen() {
  string code = "";

  for (const unique_ptr<StatementNode>& statement : statements) {
    code = code + statement->codegen();
  }

  return code;
}

string BlockNode::codegen() {
  string code = "";

  for (const unique_ptr<StatementsNode>& statement : statements) {
    code = code + statement->codegen();
  }

  return code;
}

string InitializationNode::codegen() { return "=" + expressions->codegen(); }

string DeclarationNode::codegen() {
  string code = type->codegen() + name->codegen();

  if (initialization) {
    code = code + initialization->codegen();
  }

  return code + ";";
}

string AttributeDeclarationNode::codegen() {
  string code = accessModifier->codegen();

  for (const unique_ptr<ModifierNode>& modifier : modifiers) {
    code = code + modifier->codegen();
  }

  code = code + declaration->codegen();

  return code;
}

string AttributesDeclarationNode::codegen() {
  string code = "";

  for (const unique_ptr<AttributeDeclarationNode>& attr : attributes) {
    code = code + attr->codegen();
  }

  return code;
}

string ConstructorStatementsNode::codegen() {
  string code = "";

  for (const unique_ptr<StatementWithoutReturnNode>& stmt : statements) {
    code = code + stmt->codegen();
  }

  return code;
}

string ConstructorSignatureNode::codegen() {
  return className->codegen() + "(" + parameters->codegen() + ")";
}

string ConstructorBodyNode::codegen() {
  return "{" + statements->codegen() + "}";
}

string ConstructorDeclarationNode::codegen() {
  return signature->codegen() + body->codegen();
}

string MethodSignatureNode::codegen() {
  string code = "";

  if (accessModifier) {
    code = code + accessModifier->codegen();
  }

  for (const unique_ptr<ModifierNode>& modifier : modifiers) {
    if (modifier) {
      code = code + modifier->codegen();
    }
  }

  if (returnType) {
    code = code + returnType->codegen();
  }

  code = code + methodName->codegen();
  code = code + parameters->codegen();

  return code;
}

string MethodBodyNode::codegen() {
  string code = "";

  for (const unique_ptr<StatementsNode>& stmt : statements) {
    code = code + stmt->codegen();
  }

  return code;
}

string MethodDeclarationNode::codegen() {
  return signature->codegen() + "{" + body->codegen() + "}";
}

string MethodsDeclarationNode::codegen() {
  string code = "";

  for (const unique_ptr<MethodDeclarationNode>& decl : methods) {
    code = code + decl->codegen();
  }

  return code;
}

string ClassBodyNode::codegen() {
  return attributes->codegen() + constructor->codegen() + methods->codegen();
}

string ClassDeclarationHeaderNode::codegen() { return header; }

string ClassDeclarationNode::codegen() {
  return className->codegen() + body->codegen();
}

string ProgramNode::codegen() { return classDeclaration->codegen(); }

}  // namespace ast
