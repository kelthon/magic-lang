#pragma once

#include <cstdint>
#include <iostream>

#include "langdef.h"

class FileReader {
 private:
  char peek;
  uint line;
  uint column;

 public:
  FileReader() : line(1), column(1) {};
  char getchar();
  uint getLineNumber();
  uint getColumnNumber();
  void updateLocation();
};
