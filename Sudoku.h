#include <iostream>
#include <fstream>
using namespace std;

class Sudoku {
  public:
    Sudoku(string file);
    void PrintBoard();
    void Solve();
  private:
    bool IsRowValid();
    bool IsColValid();
    bool IsBoxValid();
    int m_board[9][9];
};
