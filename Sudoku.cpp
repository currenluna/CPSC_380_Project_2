#include "Sudoku.h"

Sudoku::Sudoku(string fname) {
  ifstream fin;
  string line;
  //stringstream linestream(line);

  // Open File
  fin.open(fname);

  // Error
  if (!fin.is_open()) {
    perror("File error");
    exit(EXIT_FAILURE);
  }

  // Read contents into m_board
  int i, j = 0;
  while (getline(fin, line)) {
    if (j == 8)
      i++;
    j = (j+1) % 9;
  }

}

void Sudoku::PrintBoard() {
  cout << endl;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << m_board[i][j] << " ";
      if (j == 2 || j == 5) {
        cout << "| ";
      }
    }
    cout << endl;
    if (i == 2 || i == 5) {
      cout << "---------------------" << endl;
    }
  }
  cout << endl;
}

void Sudoku::Solve() {

}

bool Sudoku::IsRowValid() {
  return false;
}

bool Sudoku::IsBoxValid() {
  return false;
}
