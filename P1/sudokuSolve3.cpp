#include <iostream>
#include <fstream>
#include "function.h"
#define N 9
using namespace std;
int sudoku[N][N];


int main(){
	readFile();
   if (solveSudoku() == true)
      display_board();
   else
      cout << "No solution exists";
}