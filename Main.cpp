#include "Sudoku.h"

int main(int argc, char* argv[]) {

  if (argc > 1) {
    Sudoku* s = new Sudoku(argv[1]);
    s->PrintBoard();
  } else {
    cout << "No file provided." << endl;
  }
  return 0;
}
