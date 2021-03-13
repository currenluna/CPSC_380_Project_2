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
  int i = 0;
  while (getline(fin, line)) {
    string curr;
    stringstream ss(line);
    for (int j = 0; j < 9; j++) {
      getline(ss, curr, ',');
      m_boardInput[i][j] = stoi(curr);
    }
    i++;
  }

  this->PrintBoard(this->m_boardInput);
}

// Prints a Board
void Sudoku::PrintBoard(int (&board)[9][9] ) {
  cout << endl;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << board[i][j] << " ";
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
  // TODO : Write algorithm?
}

bool Sudoku::IsRowValid() {
  return false;
}

bool Sudoku::IsBoxValid() {
  return false;
}
