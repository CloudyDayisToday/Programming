#ifndef SOLVE_SUDOKU
#define SOLVE_SUDOKU


void readFile();
bool isPresentInCol(int col, int num);
bool isPresentInRow(int row, int num);
bool isPresentInBox(int startRow, int startCol, int num);
void display_board();
bool findEmptyPlace(int &row, int &col);
bool isValidPlace(int row, int col, int num);
bool solveSudoku();


#endif


