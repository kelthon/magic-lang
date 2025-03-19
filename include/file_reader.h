#pragma once

#include <cstdint>
#include <iostream>

#include "langdef.h"

class FileReader {
 private:
  char peek;
  uint line;
  uint column;
  void updatePosition();

 public:
  FileReader() : line(1), column(1) {};
  char getChar();
  uint getCurrentLine();
  uint getCurrentColumn();
};
