#include <stdio.h>
#include <stdbool.h>

void printBoard(char board[][26], int n);
void availableMoves(char board[][26], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
void flipInDirection(char board[][26], int n);

int main(int argc, char **argv) {
	int n; //board dimension
	printf("Enter the board dimension: ");
	scanf("%d", &n);
	char board[n][26]; //board[row][column]
	
	//Defining the initial board - all unoccupied
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			board[i][j]  = 'U';
		}
	}
	//defining the center pieces
	board[n/2 - 1][n/2 - 1] = 'W'; //white
	board[n/2 - 1][n/2 + 1 - 1] = 'B'; //black
	board[n/2 + 1 - 1][n/2 - 1] = 'B'; //black
	board[n/2 + 1 - 1][n/2 + 1 - 1] = 'W'; //white
	
	printBoard(board, n); //prints board
	boardConfig(board, n); //requests input for board configuration
	availableMoves(board, n); //print available moves
	flipInDirection(board, n); //request input and flip in the direction
	
	return 0;
}

void printBoard(char board[][26], int n) {
	char borderLabel[26];
	for (int i=0; i<26; i++) {//defining border label
		borderLabel[i] = 97 + i;
	}
	
	printf("  ");
	for (int i=0; i<n; i++) { //printing horizontal border
		printf("%c", borderLabel[i]);
	}
	
	printf("\n");
	for (int i=0; i<n; i++){
		printf("%c ", borderLabel[i]); //printing vertical border step-by-step
		for (int j=0; j<n; j++) {
			printf("%c", board[i][j]); //printing all board components in each step
		}
		printf("\n");
	}
}

void boardConfig(char board[][26], int n) {
	char player, row, col;
	
	printf("Enter board configuration:\n");
	do {
		scanf(" %c%c%c", &player, &row, &col); //note: enter is taken as a character as well
		if (player != '!' && row != '!' && col != '!') {
			row = row - 'a';
			col = col - 'a';
			board[row][col] = player;
		}
	} while (player != '!' && row != '!' && col != '!');
	
	printBoard(board, n);
}

void availableMoves(char board[][26], int n) {//loop to check every position if legal - print location if legal
	int row, col, player=1, deltaRow, deltaCol;
	char colour;
	bool legal;
	
	while (player>=0) {
		if (player==1) printf("Available moves for W:\n"); //player W
		else printf("Available moves for B:\n"); //player B
		
		for (row = 0; row < n; row++) {//row increment
			for (col = 0; col < n; col++) {//col increment
				if (board[row][col] != 'W' && board[row][col] != 'B') {//checking if spot taken
					if (player==1) colour = 'W'; //player W
					else colour = 'B'; //player B
					
					for (deltaRow = -1; deltaRow <=1; deltaRow++) {
						for (deltaCol = -1; deltaCol<=1; deltaCol++) {
							legal = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
							
							if (legal) {
								printf("%c%c\n", row+97, col+97); //prints location if board[row][col] is valid
								break; //because we want to move on to the next position (1/2)
							}
						}
					if (legal) break; //because we want to move on to the next position (2/2)
					}
				}
			}
		}
		player--;
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
	if (board[row][col] != 'U') return false; //returns false if position is taken (position is U if not taken)
	if (deltaRow == 0 && deltaCol == 0) return false; //false if both 0
	if (positionInBounds(n, row+deltaRow, col+deltaCol) == false) return false; //false if out of bounds
	if (board[row+deltaRow][col+deltaCol] == 'U' || board[row+deltaRow][col+deltaCol] == colour) return false; //false if immediate next position is U or same colour 
	
	for (int i=row+2*deltaRow, j=col+2*deltaCol; positionInBounds(n, i, j); i+=deltaRow, j+=deltaCol) {
		if (board[i][j] == 'U') return false;//false if U appears in the direction
		else if (board[i][j] == colour) return true;//true if it hits a same colour in the direction
	}
}

void flipInDirection(char board[][26], int n) {
	int deltaRow, deltaCol;
	char colour, row, col;
	bool legal, legalFlip;
	
	printf("Enter a move:\n");
	scanf(" %c%c%c", &colour, &row, &col);
	row = row - 'a';
	col = col - 'a';
	
	for (deltaRow = -1; deltaRow <=1; deltaRow++) {
		for (deltaCol = -1; deltaCol<=1; deltaCol++) {
			legal = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
			if (legal) break;
		}
		if (legal) break;
	}
	
	if (legal == true) {
		printf("Valid Move.\n");
		for (deltaRow = -1; deltaRow <=1; deltaRow++) {//flips the first right direction and not the rest
			for (deltaCol = -1; deltaCol<=1; deltaCol++) {
				legalFlip = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
				if (legalFlip) {// if deltaRow, deltaCol combo is legal, it starts flipping in that direction
					for (int i=row+deltaRow, j=col+deltaCol; board[i][j] != colour; i+=deltaRow, j+=deltaCol) {//segment working
						board[i][j] = colour; //assigns the position with colour
					}
				}
			}
		}
		board[row][col] = colour; //replace the position the last
	}
	
	else printf("Invalid Move.\n");
	
	printBoard(board, n);
}

