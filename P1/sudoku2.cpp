/*All the functions*/
#include <iostream>
#include <fstream>
#include <function.h>

#define N 9
void readFile(){
	fstream myfile;
	int i, j;
	myfile.open("sudoku.txt", ios::in); //It opens the file for a read
	if(!myfile){
		cout << "No such file";
	}
	else{
		char ch;
		for(i=0;i<N;i++){
			for(j=0;j<=N;j++){
				myfile.get(ch);
				if(ch=='X') ch=0;
				else ch = int(ch)-48;
				sudoku[i][j]=ch;
				cout<<sudoku[i][j]<<" ";
			}
		}
		myfile.close();
	}
	cout<<endl;
}

bool isPresentInCol(int col, int num){ //check whether num is present in col or not
   for (int row = 0; row < N; row++)
      if (sudoku[row][col] == num)
         return true;
   return false;
}
bool isPresentInRow(int row, int num){ //check whether num is present in row or not
   for (int col = 0; col < N; col++)
      if (sudoku[row][col] == num)
         return true;
   return false;
}
bool isPresentInBox(int startRow, int startCol, int num){
//check whether num is present in 3x3 box or not
   for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (sudoku[row+startRow][col+startCol] == num)
            return true;
   return false;
}
void display_board(){ //print the sudoku grid after solve
   int row, col, h=0;
   for (row = 0; row < N; row++){
	    if((row%3)==0){
			while(h<=12){
				if((h%4)==0)
					cout<<" ";
				else
					cout<<"--";
				h++;
			}
			h = 0; //reset h
			cout<<endl;
		}
      for (col = 0; col < N; col++){
         if((col%3)==0)
            cout << "|";
         cout << sudoku[row][col] <<" ";
      }
	  cout<<"|"<<endl;
   }
   while(h<=12){
		if((h%4)==0)
			cout<<" ";
		else
			cout<<"--";
		h++;
	}
}


bool findEmptyPlace(int &row, int &col){ //get empty location and update row and column
   for (row = 0; row < N; row++)
      for (col = 0; col < N; col++)
         if (sudoku[row][col] == 0) //marked with 0 is empty
            return true;
   return false;
}
bool isValidPlace(int row, int col, int num){
   //when item not found in col, row and current 3x3 box
   return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3, col - col%3, num);
}
bool solveSudoku(){
   int row, col;
   if (!findEmptyPlace(row, col))
      return true; //when all places are filled
   for (int num = 1; num <= N; num++){ //valid numbers are 1 - 9
      if (isValidPlace(row, col, num)){ //check validation, if yes, put the number in the sudoku
         sudoku[row][col] = num;
         if (solveSudoku()) //recursively go for other rooms in the sudoku
            return true;
         sudoku[row][col] = 0; //turn to unassigned space when conditions are not satisfied
      }
   }
   return false;
}