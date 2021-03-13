#include "Sudoku.h"

// Main
int main(int argc, char* argv[]) {

  // Check for file input
  if (argc > 1) {
    Sudoku* s = new Sudoku(argv[1]);
    s->Solve();
  } else {
    cout << "No file provided." << endl;
  }
  return 0;
}
