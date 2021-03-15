#include "Sudoku.h"

/* Curren Taber
 * Professor Hansen
 * CPSC 380-01
 * Project 2: Sudoku Validator
 */

// Main
int main(int argc, char* argv[]) {

  // Check for file input
  if (argc > 1) {
    Sudoku* s = new Sudoku(argv[1]);
    s->FindCoordinates();
  } else {
    cout << "No file provided." << endl;
  }
  return 0;
}
