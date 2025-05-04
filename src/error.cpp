#include "error.h"

#include <string>

using std::string;

const char* SyntaxError::what() const noexcept {
  auto msg = "SyntaxError: " + message;
  return msg.c_str();
}