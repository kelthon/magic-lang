#include "file_reader.h"

#include <cstdint>
#include <fstream>
#include <iostream>

extern std::ifstream fin;

void FileReader::updatePosition() {
  column++;

  if (peek == NEWLINE_CHAR) {
    line++;
    column = 1;
  }
}

char FileReader::getChar() {
  peek = fin.get();
  updatePosition();

  return peek;
}

uint FileReader::getCurrentLine() { return line; }

uint FileReader::getCurrentColumn() { return column; }
