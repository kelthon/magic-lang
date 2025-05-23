#include "errors.h"

#include <string>

using std::string;

const char* SyntaxError::what() const noexcept {
  return message.c_str();
}