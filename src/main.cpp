#include <fstream>
#include <iomanip>
#include <iostream>

#include "file_reader.h"

std::ifstream fin;

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Usage: magic <filename>" << endl;
    return 1;
  } else {
    fin.open(argv[1]);

    uint pos = 0;
    char peek = '\n';
    FileReader reader;

    if (!fin.is_open()) {
      cerr << "No such file or directory" << endl;
      return 1;
    }

    do {
      if (peek == '\n') {
        if (pos != 0) {
          cout << '\n' << "   " << " | ";

          for (uint i = 1; i < pos; i++) {
            cout << '~';
          }
          cout << '^';
          pos = 0;
        }

        cout << "\n" << setw(3) << reader.getLineNumber() << " | ";
      } else {
        cout << peek;
      }

      if (peek == 'f') pos = reader.getColumnNumber();
      peek = reader.getchar();
    }

    while (peek != EOF);
    cout << endl;

    fin.close();
  }

  return 0;
}
