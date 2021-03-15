#include "Sudoku.h"


int m_boardInput[N][N];
int m_boardDuplicates[N][N];
int m_boardSolution[N][N];

// Overloaded Constructor
Sudoku::Sudoku(string fname) {
  ifstream fin;
  string line;
  fin.open(fname);

  // Error
  if (!fin.is_open()) {
    perror("File error");
    exit(EXIT_FAILURE);
  }

  // Read contents into m_boardInput
  int i = 0;
  while (getline(fin, line)) {
    string curr;
    stringstream ss(line);
    for (int j = 0; j < N; j++) {
      getline(ss, curr, ',');
      m_boardInput[i][j] = stoi(curr);
      m_boardSolution[i][j] = stoi(curr);
      m_boardDuplicates[i][j] = 0;
    }
    i++;
  }
  cout << endl << "INPUT:" << endl;
  this->PrintBoard(m_boardInput);
}

// Prints a Board
void Sudoku::PrintBoard(int (&board)[N][N] ) {
  cout << endl;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
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

// Finds problematic coordinates and zeros them
void Sudoku::FindCoordinates() {
  // TODO
  pthread_t tid_row;
  pthread_t tid_col;
  pthread_t tid_box;


  pthread_create(&tid_row, NULL, &FindRowDuplicates, NULL);
  pthread_create(&tid_col, NULL, &FindColDuplicates, NULL);
  pthread_create(&tid_box, NULL, &FindBoxDuplicates, NULL);

  pthread_join(tid_row, NULL);
  pthread_join(tid_col, NULL);
  pthread_join(tid_box, NULL);

  // Zero out problematic coordinates
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (m_boardDuplicates[i][j] > 1) {
        m_boardSolution[i][j] = 0;
      }
    }
  }

  // Solve zeroed answer board
  this->Solve(m_boardSolution);

  PrintBoard(m_boardSolution);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      // Problematic coordinate
      if (m_boardDuplicates[i][j] > 1) {
        cout << "Change ROW[" << i+1 << "] COL[" << j+1 << "] to " << m_boardSolution[i][j] << endl;
      }
    }
  }
  cout << endl << "Done!" << endl;
  pthread_exit(NULL);
}

// Finds duplicate #s in each row
void* Sudoku::FindRowDuplicates(void* arg) {
  for (int i = 0; i < N; i++) {
    unordered_set<int> seen;
    unordered_set<int> dups;
    for (int j = 0; j < N; j++) {
      if (seen.find(m_boardInput[i][j]) == seen.end()) {
        seen.insert(m_boardInput[i][j]);
      } else {
        dups.insert(m_boardInput[i][j]);
      }
    }
    for (int j = 0; j < N; j++) {
      if (dups.find(m_boardInput[i][j]) != dups.end()) {
        m_boardDuplicates[i][j]++;
      }
    }
  }
  pthread_exit(0);
}

// Finds duplicate #s in each col
void* Sudoku::FindColDuplicates(void* arg) {
  for (int i = 0; i < N; i++) {
    unordered_set<int> seen;
    unordered_set<int> dups;
    for (int j = 0; j < N; j++) {
      if (seen.find(m_boardInput[j][i]) == seen.end()) {
        seen.insert(m_boardInput[j][i]);
      } else {
        dups.insert(m_boardInput[j][i]);
      }
    }
    for (int j = 0; j < N; j++) {
      if (dups.find(m_boardInput[j][i]) != dups.end()) {
        m_boardDuplicates[j][i]++;
      }
    }
  }
  pthread_exit(0);
}

// Finds duplicate #s in each box
void* Sudoku::FindBoxDuplicates(void* arg) {
  // Iterates top-left corner of each box
  for (int i = 0; i < N; i+=3) {
    for (int j = 0; j < N; j+=3) {

      unordered_set<int> seen;
      unordered_set<int> dups;
      for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
          if (seen.find(m_boardInput[i+x][j+y]) == seen.end()) {
            seen.insert(m_boardInput[i+x][j+y]);
          } else {
            dups.insert(m_boardInput[i+x][j+y]);
          }
        }
      }
      for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
          if (dups.find(m_boardInput[i+x][j+y]) != dups.end()) {
            m_boardDuplicates[i+x][j+y]++;
          }
        }
      }
    }
  }
  pthread_exit(0);
}

// Checks a number in a cell for validity
bool Sudoku::IsValid(int board[N][N], int row, int col, int num) {

  // False if found instance of number to check in same row
  for (int i = 0; i < N; i++) {
    if (board[row][i] == num) {
      return false;
    }
  }

  // False if found instance of number to check in same column
  for (int i = 0; i < N; i++) {
    if (board[i][col] == num) {
      return false;
    }
  }

  // False if found instance of number to check in same box
  int startRow = row - (row % 3);
  int startCol = col - (col % 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[startRow+i][startCol+j] == num) {
        return false;
      }
    }
  }

  // All good!
  return true;
}

// Looks for next empty cell
bool Sudoku::FoundEmpty(int board[N][N], int& row, int& col) {
  for (row = 0; row < N; row++) {
    for (col = 0; col < N; col++) {
      if (board[row][col] == 0) {
        //cout << row << " " << col << endl;
        return true;
      }
    }
  }
  return false;
}

// Creates solution for unassigned spaces
bool Sudoku::Solve(int board[N][N]) {

  int row = 0;
  int col = 0;

  if (!FoundEmpty(board, row, col)) {
    return true;
  }

  // Backtracking algorithm
  for (int num = 1; num <= N; num++) {
    if (IsValid(board, row, col, num)) {
      board[row][col] = num;
      if (Solve(board)) {
        return true;
      }
    }
    board[row][col] = 0; // Unassign for next attempt
  }


  return false;
}
