#include <iostream>
#include <fstream>
#include <sstream>
#include <pthread.h>
using namespace std;

class Sudoku {
  public:
    Sudoku(string file);
    void PrintBoard(int (&board)[9][9]); // Prints a Board
    void Solve();
  private:
    int m_boardInput[9][9];
    static void* runner_rows(void* arg);

    bool IsRowValid();
    bool IsColValid();
    bool IsBoxValid();
};
