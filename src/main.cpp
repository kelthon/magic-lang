#include <fstream>
#include <iomanip>
#include <iostream>

#include "file_reader.h"
#include "langdef.h"
#include "lexer.h"

std::ifstream fin;

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Usage: magic <filename>" << endl;
    return 1;
  } else {
    fin.open(argv[1]);

    if (!fin.is_open()) {
      cerr << "No such file or directory" << endl;
      return 1;
    }

    Lexer scanner;

    scanner.scan()->toString();
    cout << "" << endl;
    scanner.scan()->toString();
    cout << "" << endl;

    fin.close();
  }

  return 0;
}
