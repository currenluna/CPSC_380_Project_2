#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Sudoku {
  public:
    Sudoku(string file);
    void PrintBoard(int (&board)[9][9]); // Prints a Board
    void Solve();
  private:
    bool IsRowValid();
    bool IsColValid();
    bool IsBoxValid();
    int m_boardInput[9][9];
};
