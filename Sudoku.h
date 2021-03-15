#include <iostream>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <unordered_set>
using namespace std;

/* Curren Taber
 * Professor Hansen
 * CPSC 380-01
 * Project 2: Sudoku Validator
 */

// Dimension of Board
#define N 9

// Global Variables
extern int m_boardInput[N][N]; // Board from Input
extern int m_boardDuplicates[N][N]; // Board with Duplicate Count
extern int m_boardSolution[N][N]; // Board with Solution

class Sudoku {
  public:
    Sudoku(string file); // Overloaded Constructor
    void PrintBoard(int (&board)[N][N]); // Prints a Board
    void FindCoordinates(); // Finds problematic coordinates and zeros them
  private:
    static void* FindRowDuplicates(void* arg); // Finds duplicate #s in each row
    static void* FindColDuplicates(void* arg); // Finds duplicate #s in each col
    static void* FindBoxDuplicates(void* arg); // Finds duplicate #s in each box
    bool IsValid(int board[N][N], int row, int col, int num); // Checks a number in a cell for validity
    bool FoundEmpty(int board[N][N], int& row, int& col); // Looks for next empty cell
    bool Solve(int board[N][N]); // Creates solution for unassigned cells
};
