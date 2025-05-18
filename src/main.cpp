#include <fstream>
#include <iomanip>
#include <iostream>

#include "file_reader.h"
#include "langdef.h"
#include "lexer.h"
#include "parser.h"

std::ifstream fin;

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fin.open("../resources/source.txt");

    if (!fin.is_open()) {
      fin.open("./resources/source.txt");
    }

    if (!fin.is_open()) {
      cerr << "Usage: magic <filename>" << endl;
      return 1;
    }
  } else {
    fin.open(argv[1]);

    if (!fin.is_open()) {
      cerr << "No such file or directory" << endl;
      return 1;
    }
  }

  Lexer lex;
  Parser parser = Parser(&lex);

  auto tokens = parser.parse();

  cout << tokens << endl;

  return 0;
}
