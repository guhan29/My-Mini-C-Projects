#include<stdio.h>
#include<string.h>

#define S 9

// I compiled it with c99 mode
// Use gcc -Wall -o "wordoku" -std=c99 "wordoku.c" to compile

void printBoard(char board[S][S]) {
	for(int i=0; i<S; i++) {
		for (int j=0; j<S; j++) {
			if((j+1)%3 == 0 && j != 8) printf(" %c  | ", board[i][j]);
			else printf(" %c ", board[i][j]);
		}
		printf("\n");
		if((i+1)%3 == 0 && i != 8) printf("----------+-----------+----------\n");
	}
}

int isThereEmptySpace(char board[S][S], int *row, int *col) {
	for(int i=0; i<S; i++) 
		for(int j=0; j<S; j++) 
			if(board[i][j] == '_') {
				*row = i;
				*col = j;
				return 1;
			}
	return 0;
}

int isSafe(char board[S][S], int row, int col, char ch) {
	
	// Check for the number in row and column
	for(int i=0; i<S; i++)
		if(board[row][i] == ch || board[i][col] == ch)
			return 0;
	
	// Initializing the start index of the square
	int startRow = row - row%3;
	int startCol = col - col%3;
	
	// Check for the number in the square	
	for(int i=startRow; i<startRow+3; i++)
		for(int j=startCol; j<startCol+3; j++)
			if(board[i][j] == ch) return 0;
			
	return 1;
}
	
	

int sudokuSolver(char board[S][S]) {
	int row, col;
	
	// Check whether there is any empty space
	if(!isThereEmptySpace(board, &row, &col)) return 1;
	
	// Loop through all possible values
	for(int i='A'; i<='Z'; i++) {
		if(isSafe(board, row, col, (char) i)) {
			
			// Assigning the Character
			board[row][col] = (char) i;
			
			// Recursive call to check it whether the Character is correct for the position
			if(sudokuSolver(board)) return 1;
			
			// If it is not correct for the corresponding position the value is set to '_'
			board[row][col] = '_';
		}
	}
	// If recursive call finds any of the characters from A to Z is not safe for the corresponding
	// position on the board it returns 0
	// Thus it triggers backtracking
	return 0;
}

int main() {
	char board[S][S] = {{'_', '_', 'E', 'R', '_', 'N', '_', '_', 'D'},  
                      {'_', '_', '_', '_', '_', '_', 'N', '_', '_'},  
                      {'_', '_', 'N', '_', 'O', '_', '_', '_', 'R'},  
                      {'_', 'O', '_', 'N', '_', 'L', '_', '_', 'S'},  
                      {'_', '_', 'S', '_', 'R', '_', 'D', '_', '_'},  
                      {'R', '_', '_', 'O', '_', 'A', '_', 'I', '_'},  
                      {'D', '_', '_', '_', 'N', '_', 'L', '_', '_'},  
                      {'_', '_', 'L', '_', '_', '_', '_', '_', '_'},  
                      {'S', '_', '_', 'A', '_', 'E', 'O', '_', '_'}};
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
