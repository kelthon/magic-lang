#pragma once

#include <exception>
#include <iostream>

using std::exception;
using std::string;

class SyntaxError : public exception {
 protected:
  string message;

 public:
  SyntaxError() : message("A SyntaxError has occurred") {}
  explicit SyntaxError(const string& message) : message(message) {}
  const char* what() const noexcept override;
};
