#include<stdio.h>

#define S 9

// I compiled it with c99 mode
// Use gcc -Wall -o "solver" -std=c99 "solver.c" to compile

void printBoard(int board[S][S]) {
	for(int i=0; i<S; i++) {
		for (int j=0; j<S; j++) {
			if((j+1)%3 == 0 && j != 8) printf(" %d  | ", board[i][j]);
			else printf(" %d ", board[i][j]);
		}
		printf("\n");
		if((i+1)%3 == 0 && i != 8) printf("----------+-----------+----------\n");
	}
}

int isThereEmptySpace(int board[S][S], int *row, int *col) {
	for(int i=0; i<S; i++) 
		for(int j=0; j<S; j++) 
			if(board[i][j] == 0) {
				*row = i;
				*col = j;
				return 1;
			}
	return 0;
}

int isSafe(int board[S][S], int row, int col, int num) {
	
	// Check for the number in row and column
	for(int i=0; i<S; i++)
		if(board[row][i] == num || board[i][col] == num)
			return 0;
	
	// Initializing the start index of the square
	int startRow = row - row%3;
	int startCol = col - col%3;
	
	// Check for the number in the square	
	for(int i=startRow; i<startRow+3; i++)
		for(int j=startCol; j<startCol+3; j++)
			if(board[i][j] == num) return 0;
			
	return 1;
}
	
	

int sudokuSolver(int board[S][S]) {
	int row, col;
	
	// Check whether there is any empty space
	if(!isThereEmptySpace(board, &row, &col)) return 1;
	
	// Loop through all possible values
	for(int i=1; i<=S; i++) {
		if(isSafe(board, row, col, i)) {
			
			// Assigning the number
			board[row][col] = i;
			
			// Recursive call to check it the number is correct for the position
			if(sudokuSolver(board)) return 1;
			
			// If it is not correct for the corresponding position the value is set to 0
			board[row][col] = 0;
		}
	}
	// If recursive call finds any of the numbers 1 to 9 is not safe for the corresponding
	// position on the board it returns 0
	// Thus it triggers backtracking
	return 0;
}

int main() {
	int board[S][S] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},  
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},  
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},  
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},  
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},  
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},  
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},  
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},  
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};
	puts("The given Sudoku: \n");
	printBoard(board);
	printf("\n\n");         
	if(sudokuSolver(board)) {
		puts("The solved sudoku is: \n");
		printBoard(board);
	}
	else
		puts("It is impossible to solve this sudoku");

	return 0;
}
