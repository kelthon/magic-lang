#include "file_reader.h"

#include <cstdint>
#include <fstream>
#include <iostream>

extern std::ifstream fin;

void FileReader::updateLocation() {
  column++;

  if (peek == NEWLINE_CHAR) {
    line++;
    column = 1;
  }
}

char FileReader::getchar() {
  char nextChar = fin.get();
  updateLocation();

  if (nextChar == std::istream::traits_type::eof()) {
    return EOF;
  }

  peek = static_cast<char>(nextChar);
  return peek;
}

uint FileReader::getLineNumber() { return line; }

uint FileReader::getColumnNumber() { return column; }
