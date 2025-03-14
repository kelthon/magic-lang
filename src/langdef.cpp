#include "langdef.h"

#include <iostream>

using std::string;

int isoperator(char character) {
  string charset = "-:!.*/&%^+<=>|~";
  std::size_t pos = charset.find(character);

  return pos >= 0 && pos < charset.length();
}