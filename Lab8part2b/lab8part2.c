/*
 * 
 */

#include <stdio.h>
#include <stdbool.h>
//#include "lab8part2lib.h"

void printBoard(char board[][26], int n);
bool availableMovesForHuman(char board[][26], int n, char colour);
int availableMovesForHumanCounter(char board[][26], int n, char colour);
void boardConfig(char board[][26], int n);
void availableMovesForComp(char board[][26], int n, char colour, char *bestRow, char *bestCol);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
void flipBoard(char board[][26], int n, char colour, char row, char col);
void playHuman(char board[][26], int n, char colour, bool *invalidHuman, bool *noMovesHuman);
void playComp(char board[][26], int n, char colour, bool *noMovesComp);
int computeScore(char board[][26], int n, char colour, int row, int col);
char identifyWinner(char board[][26], int n);
bool gameOver(char board[][26], int n, bool invalidHuman, bool noMovesHuman, bool noMovesComp);
void duplicateBoard(char board[][26], int n, char boardCopy[][26]);
int opponentNextMovesCounter(char board[][26], int n, int row, int col, char colour);

int main(int argc, char **argv) {
	int n, i, j; //board dimension
	printf("Enter the board dimension: ");
	scanf("%d", &n);
	char board[n][26]; //board[row][column]
	
	//Defining the initial board - all unoccupied
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			board[i][j]  = 'U';
		}
	}
	//defining the center pieces
	board[n/2 - 1][n/2 - 1] = 'W'; //white
	board[n/2 - 1][n/2 + 1 - 1] = 'B'; //black
	board[n/2 + 1 - 1][n/2 - 1] = 'B'; //black
	board[n/2 + 1 - 1][n/2 + 1 - 1] = 'W'; //white
	
	//Defining for comp's and player's colour
	char compColour;
	printf("Computer plays (B/W): ");
	scanf(" %c", &compColour);
	printBoard(board, n);
	
	//initiating game
	bool invalidHuman = false, noMovesHuman = false, noMovesComp = false;
	if (compColour == 'B') {
		int count = 1;
		do {
			if (count%2 != 0) playComp(board, n, 'B', &noMovesComp);
			else playHuman(board, n, 'W', &invalidHuman, &noMovesHuman);
			if (invalidHuman == true) break;
			count++;
		} while (gameOver(board, n, invalidHuman, noMovesHuman, noMovesComp) == false); 
	} else {
		int count = 1;
		do {
			if (count%2 != 0) playHuman(board, n, 'B', &invalidHuman, &noMovesHuman);
			else playComp(board, n, 'W', &noMovesComp);
			if (invalidHuman == true) break;
			count++;
		} while (gameOver(board, n, invalidHuman, noMovesHuman, noMovesComp) == false); 
	}
	
	//game is over - check who's the winnner
	char winner = identifyWinner(board, n);
	if (invalidHuman == true) {
		printf("%c player wins.\n", compColour);
	} else if (winner == 'U') {//signifies draw
		printf("Draw!");
	} else {
		printf("%c player wins.\n", winner);
	}
	
	return 0;
}

void printBoard(char board[][26], int n) {
	int i, j;
	char borderLabel[26];
	for (i=0; i<26; i++) {//defining border label
		borderLabel[i] = 97 + i;
	}
	
	printf("  ");
	for (i=0; i<n; i++) { //printing horizontal border
		printf("%c", borderLabel[i]);
	}
	
	printf("\n");
	for (i=0; i<n; i++){
		printf("%c ", borderLabel[i]); //printing vertical border step-by-step
		for (j=0; j<n; j++) {
			printf("%c", board[i][j]); //printing all board components in each step
		}
		printf("\n");
	}
}

bool positionInBounds(int n, int row, int col) {//checks whether the specified (row, col) lies within the board dimensions
	if (row < n && row >= 0 && col < n && col >= 0) 
		return true; //Means yes, it is in bounds
	else 
		return false;
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
	//attempting to combine all 8
	int i, j;
	
	if (board[row][col] != 'U') return false; //returns false if position is taken (position is U if not taken)
	if (deltaRow == 0 && deltaCol == 0) return false; //false if both 0
	if (positionInBounds(n, row+deltaRow, col+deltaCol) == false) return false; //false if out of bounds
	if (board[row+deltaRow][col+deltaCol] == 'U' || board[row+deltaRow][col+deltaCol] == colour) return false; //false if immediate next position is U or same colour 
	
	for (i=row+2*deltaRow, j=col+2*deltaCol; positionInBounds(n, i, j); i+=deltaRow, j+=deltaCol) {
		if (board[i][j] == 'U') return false;//false if U appears in the direction
		else if (board[i][j] == colour) return true;//true if it hits a same colour in the direction
	}
}

void flipBoard(char board[][26], int n, char colour, char row, char col) {
	int deltaRow, deltaCol, i, j;
	bool legalFlip;
	
	row = row - 'a';//revert back to index
	col = col - 'a';
	
	for (deltaRow = -1; deltaRow <=1; deltaRow++) {//flips the first right direction and not the rest
		for (deltaCol = -1; deltaCol<=1; deltaCol++) {
			legalFlip = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
			if (legalFlip) {// if deltaRow, deltaCol combo is legal, it starts flipping in that direction
				for (i=row+deltaRow, j=col+deltaCol; board[i][j] != colour; i+=deltaRow, j+=deltaCol) {//segment working
					board[i][j] = colour; //assigns the position with colour
				}
			}
		}
	}
	board[row][col] = colour; //replace the position the last
}

void duplicateBoard(char board[][26], int n, char boardCopy[][26]) {
	int row, col;
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			boardCopy[row][col] = board[row][col];
		}
	}
}

void playComp(char board[][26], int n, char colour, bool *noMovesComp) {
	char row = '-', col = '-';
	char * bestRow;
	char * bestCol;
	
	bestRow = &row; //adress of row is stored in bestRow
	bestCol = &col;
	
	availableMovesForComp(board, n, colour, bestRow, bestCol); //modifies position array and stores index values of row and col of best position to play
	
	if (row == '-' && col == '-') {//position is unchanged as no available moves
		printf("%c player has no valid move.\n", colour);
		*noMovesComp = true;
	} else {
		flipBoard(board, n, colour, row, col);
		printf("Computer places %c at %c%c.\n", colour, row, col);
		printBoard(board, n);
		*noMovesComp = false;
	}
}

int computeScore(char board[][26], int n, char colour, int row, int col) {
	int deltaRow, deltaCol, i, j;
	bool legalFlip;
	int score = 0;
	
	for (deltaRow = -1; deltaRow <=1; deltaRow++) {//flips the first right direction and not the rest
		for (deltaCol = -1; deltaCol<=1; deltaCol++) {
			legalFlip = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
			if (legalFlip) {
				for (i=row+deltaRow, j=col+deltaCol; board[i][j] != colour; i+=deltaRow, j+=deltaCol) {
					score++;
				}
			}
		}
	}
	
	return score;
}

void availableMovesForComp(char board[][26], int n, char colour, char *bestRow, char *bestCol) {//explicit function for Computer Play
	int maxScore = 0;
	int row, col;
	// a b c are constants
	int a = 3;
	int b = 2;
	int c = 1;
	int boardScore[26][26] = {0};
	
	//total number of flip score
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			boardScore[row][col] = a*computeScore(board, n, colour, row, col);
		}
	}
	
	//adding bonus scores to corners
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			if ((row == 0 && col == 0) || (row == n-1 && col == 0) || (row == 0 && col == n-1) || (row == n-1 && col == n-1))
				if (boardScore[row][col] != 0) //it should be a legal move - flipscore only counts to legal moves
					boardScore[row][col] = boardScore[row][col] + b;
		}
	}
	
	//counting number of available moves for humanAI
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			if (boardScore[row][col] != 0) {//it should be a legal move - flipscore only counts to legal moves
				boardScore[row][col] = boardScore[row][col] + c*opponentNextMovesCounter(board, n, row, col, colour);
			}
		}
	}
	
	//deciding best position and manipulating pointer
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			if (boardScore[row][col] > maxScore){
				maxScore = boardScore[row][col];
				*bestRow = row + 'a'; //index + a
				*bestCol = col + 'a';
			}
		}
	}
}

int opponentNextMovesCounter(char board[][26], int n, int row, int col, char colour) {
	int deltaRow, deltaCol, movesCounter = 0;
	char boardCopy[n][26]; 
	bool legal;
	
	duplicateBoard(board, n, boardCopy);
	boardCopy[row][col] = colour;
	
	for (deltaRow = -1; deltaRow <=1; deltaRow++) {
		for (deltaCol = -1; deltaCol<=1; deltaCol++) {
			legal = checkLegalInDirection(boardCopy, n, row, col, colour, deltaRow, deltaCol);
			if (legal) {
				movesCounter++; //prints location if board[row][col] is valid
				break; //because we want to move on to the next position (1/2)
			}
		}
		if (legal) break; //because we want to move on to the next position (2/2)
	}
	
	return movesCounter;
}

/*int availableMovesForHumanCounter(char board[][26], int n, char colour) {
	int row, col, deltaRow, deltaCol, movesCounter = 0;
	bool legal;
	
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			if (board[row][col] != 'W' && board[row][col] != 'B') {//checking if spot taken
				for (deltaRow = -1; deltaRow <=1; deltaRow++) {
					for (deltaCol = -1; deltaCol<=1; deltaCol++) {
						legal = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
						if (legal) {
							movesCounter++; //prints location if board[row][col] is valid
							break; //because we want to move on to the next position (1/2)
						}
					}
				if (legal) break; //because we want to move on to the next position (2/2)
				}
			}
		}
	}
	
	return movesCounter;
}*/

void playHuman(char board[][26], int n, char colour, bool *invalidHuman, bool *noMovesHuman) {
	int deltaRow, deltaCol;
	int row, col; //index
	bool legal;
	if (availableMovesForHuman(board, n, colour) == true) {
		printf("Enter move for colour %c (RowCol): ", colour);
		scanf(" %c%c", &row, &col);
//		findSmarterMove(board, n, colour, &row, &col);
//		printf("Testing AI move (row, col): %c%c\n", row + 'a', col + 'a');
		for (deltaRow = -1; deltaRow <=1; deltaRow++) {
			for (deltaCol = -1; deltaCol<=1; deltaCol++) {
				legal = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
				if (legal) break;
			}
			if (legal) break;
		}
		
		if (legal) {
			flipBoard(board, n, colour, row + 'a', col + 'a'); //invalid moves for player is checked here
			printBoard(board, n);
		} else {
			printf("Invalid Move.\n");
			*invalidHuman = true;
		}
		*noMovesHuman = false;
	} else {
		printf("%c player has no valid move.\n", colour);
		*noMovesHuman = true;
	}
}

bool availableMovesForHuman(char board[][26], int n, char colour) {//loop to check every position if legal - print location if legal
	int row, col, deltaRow, deltaCol;
	bool legal;
	
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			if (board[row][col] != 'W' && board[row][col] != 'B') {//checking if spot taken
				for (deltaRow = -1; deltaRow <=1; deltaRow++) {
					for (deltaCol = -1; deltaCol<=1; deltaCol++) {
						legal = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
						if (legal) {
							return true; //prints location if board[row][col] is valid
							break; //because we want to move on to the next position (1/2)
						}
					}
				if (legal) break; //because we want to move on to the next position (2/2)
				}
			}
		}
	}
	
	return false;
}

char identifyWinner(char board[][26], int n) {
	int row, col;
	int U = 0, W = 0, B = 0;
	
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			if (board[row][col] == 'W') W++;
			else if (board[row][col] == 'B') B++;
			else U++;
		}
	}
	
	if (W > B) return 'W';
	else if (B > W) return 'B';
	else return 'U'; //means draw
}

bool gameOver(char board[][26], int n, bool invalidHuman, bool noMovesHuman, bool noMovesComp) {//false = game is not over & true = game is over
	int row, col, unoccupiedCount = 0;
	
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			if (board[row][col] == 'U') unoccupiedCount++;
		}
	}
	
	if (unoccupiedCount == 0) return true; //0 spaces are unoccupied, meaning game is over (game over is true)
	else if (noMovesHuman == false || noMovesComp == false) return false; //if move available for human or comp, game is not over (game over is false)
	else return true;
}