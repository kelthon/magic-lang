#pragma once

#include <cstdint>
#include <iostream>

#define ZERO_DIGIT_CHAR 48
#define SPACE_CHAR 32
#define NEW_LINE_CHAR 10
#define TAB_CHAR 9

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
