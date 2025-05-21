#include "errors.h"

#include <string>

using std::string;

const char* SyntaxError::what() const noexcept {
  string reason = "Invalid Syntax: " + message;
  return reason.c_str();
}