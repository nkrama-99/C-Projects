/*
 * there's a problem at the last step
 * when just one position is available: it says-
 * W has no moves(COMP)
 * And prints W is winner
 * When it should have asked for B(HUMAN) for a move - last move
 */

#include <stdio.h>
#include <stdbool.h>

void printBoard(char board[][26], int n);
//bool availableMovesForHuman(char board[][26], int n);
bool availableMovesForHuman(char board[][26], int n, char colour);
void boardConfig(char board[][26], int n);
//void availableMovesForComp(char board[][26], int n, char position[2], char colour);
void availableMovesForComp(char board[][26], int n, char colour, char *bestRow, char *bestCol);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol);
void flipBoard(char board[][26], int n, char colour, char row, char col);
void playHuman(char board[][26], int n, char colour, bool *invalidHuman, bool *noMovesHuman);
void playComp(char board[][26], int n, char colour, bool *noMovesComp);
int computeScore(char board[][26], int n, char colour, int row, int col);
char identifyWinner(char board[][26], int n);
bool gameOver(char board[][26], int n);

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
	
	//Defining for comp's and player's colour
//	boardConfig(board, n);
	
	char compColour, humanColour;
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
//		} while (gameOver(board, n) == false); 
		} while (noMovesHuman == false && noMovesComp == false); 
	} else {
		int count = 1;
		do {
			if (count%2 != 0) playHuman(board, n, 'B', &invalidHuman, &noMovesHuman);
			else playComp(board, n, 'W', &noMovesComp);
			if (invalidHuman == true) break;
			count++;
//		} while (gameOver(board, n) == false); 
		} while (noMovesHuman == false && noMovesComp == false); 
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

/*void availableMovesForComp(char board[][26], int n, char colour, char *bestRow, char *bestCol) {//explicit function for Computer Play
	int row, col, deltaRow, deltaCol;
	bool legal;
	int count = 1, score1 = 0, score2 = 0;
	int tempPositionScore1[2] = {0}; //saves index number of row and col from score1
	int tempPositionScore2[2] = {0}; //saves index number of row and col from score2
		
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			if (board[row][col] != 'W' && board[row][col] != 'B') {//checking if spot taken
				for (deltaRow = -1; deltaRow <=1; deltaRow++) {
					for (deltaCol = -1; deltaCol<=1; deltaCol++) {
						legal = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
						if (legal) {//if legal begin
							if (count%2 != 0) {
								score1 = computeScore(board, n, colour, row, col);
								if (score1 >= score2) {
									*bestRow = row + 'a'; //index + a 
									*bestCol = col + 'a';
								}
							} else {
								score2 = computeScore(board, n, colour, row, col);
								if (score2 >= score1) {
									*bestRow = row + 'a'; //index + a
									*bestCol = col + 'a';
								}
							}
							count++;
							break; //because we want to move on to the next position (1/2)
						} //if legal end
					}
				if (legal) break; //because we want to move on to the next position (2/2)
				}
			}
		}
	}
}*/

//void availableMovesForComp(char board[][26], int n, char colour, char *bestRow, char *bestCol) {//explicit function for Computer Play
//	int maxScore = 0;
//	int boardScore[26][26] = {0};
//	int row, col;
//	
//	for (row = 0; row < n; row++) {//row increment
//		for (col = 0; col < n; col++) {//col increment
//			boardScore[row][col] = computeScore(board, n, colour, row, col);
////			printf("Score at position %c%c is %d\n", row+'a', col+'a', boardScore[row][col]);
//		}
//	}
//		for (col = 0; col < n; col++) {//col increment
//			for (deltaRow = -1; deltaRow <=1; deltaRow++) {
//				for (deltaCol = -1; deltaCol<=1; deltaCol++) {
//					legal = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
//					if (legal) {
//						if (boardScore[row][col] >= maxScore) {
//							*bestRow = row + 'a'; //index + a
//							*bestCol = col + 'a';
//						}
//					if(legal) break;
//					}
//				if(legal) break;
//				}
//			}
//		}
//	}*/
//	
//	for (row = 0; row < n; row++) {//row increment
//		for (col = 0; col < n; col++) {//col increment
//			if (boardScore[row][col] > maxScore){
//				maxScore = boardScore[row][col];
//				*bestRow = row + 'a'; //index + a
//				*bestCol = col + 'a';
////				printf("Best Score of %d at position %c%c\n", boardScore[row][col], *bestRow, *bestCol);
//			}
//		}
//	}
//	
//	//POINTERS ARE CORRECT
////	*bestCol = 3 + 'a';
////	*bestRow = 2 + 'a';
//}

void availableMovesForComp(char board[][26], int n, char colour, char *bestRow, char *bestCol) {//explicit function for Computer Play
	int maxScore = 0;
	int row, col;
	
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			if (computeScore(board, n, colour, row, col) > maxScore){
				maxScore = computeScore(board, n, colour, row, col);
				*bestRow = row + 'a'; //index + a
				*bestCol = col + 'a';
				printf("Best Score of %d at position %c%c\n", maxScore, *bestRow, *bestCol);
			}
		}
	}
}

/*bool availableMovesForHuman(char board[][26], int n) {//loop to check every position if legal - print location if legal
	int row, col, player=1, deltaRow, deltaCol;
	char colour;
	bool legal;
	
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			if (board[row][col] != 'W' && board[row][col] != 'B') {//checking if spot taken
				if (player==1) colour = 'W'; //player W
				else colour = 'B'; //player B
				
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
}*/

bool availableMovesForHuman(char board[][26], int n, char colour) {//loop to check every position if legal - print location if legal
	int row, col, deltaRow, deltaCol;
//	char colour;
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

/*void flipBoard(char board[][26], int n, char colour, char row, char col) {
	int deltaRow, deltaCol;
	bool legal, legalFlip;
	
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
	
	else {//print invalid move and detect current winner - just for human
		printf("Invalid Move.\n");
//		detectWinner();
	}
	
}*/

void flipBoard(char board[][26], int n, char colour, char row, char col) {
	int deltaRow, deltaCol;
	bool legal, legalFlip;
	
	row = row - 'a';//revert back to index
	col = col - 'a';
	
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

void playHuman(char board[][26], int n, char colour, bool *invalidHuman, bool *noMovesHuman) {
//bool playHuman(char board[][26], int n, char colour) {
	int deltaRow, deltaCol;
	char row, col;
	bool legal;
	if (availableMovesForHuman(board, n, colour) == true) {
		printf("Enter move for colour %c (RowCol): ", colour);
		scanf(" %c%c", &row, &col);
		for (deltaRow = -1; deltaRow <=1; deltaRow++) {
			for (deltaCol = -1; deltaCol<=1; deltaCol++) {
				legal = checkLegalInDirection(board, n, row - 'a', col - 'a', colour, deltaRow, deltaCol);
				if (legal) break;
			}
			if (legal) break;
		}
		
		if (legal) {
			flipBoard(board, n, colour, row, col); //invalid moves for player is checked here
			printBoard(board, n);
		} else {
			printf("Invalid Move.\n");
			*invalidHuman = true;
			//print winner and end game
		}
		*noMovesHuman = false;
	} else {
		printf("%c player has no valid move.\n", colour);
		*noMovesHuman = true;
	}
}

void playComp(char board[][26], int n, char colour, bool *noMovesComp) {
	char position[2] = {'X', 'X'};
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

/*bool playComp(char board[][26], int n, char colour) {
	char position[2] = {'X', 'X'};
	char row = '-', col = '-';
	char * bestRow;
	char * bestCol;
	
	bestRow = &row; //adress of row is stored in bestRow
	bestCol = &col;
	
	availableMovesForComp(board, n, colour, bestRow, bestCol); //modifies position array and stores index values of row and col of best position to play
	
	if (row == '-' && col == '-') {//position is unchanged as no available moves
		printf("%c player has no valid move.\n", colour);
		return true; //game on
	} else {
		flipBoard(board, n, colour, row, col);
		printf("Computer places %c at %c%c.\n", colour, row, col);
		printBoard(board, n);
//		return true; //game on
	}
}*/

int computeScore(char board[][26], int n, char colour, int row, int col) {
	int deltaRow, deltaCol;
	bool legalFlip;
	int score = 0;
	
	for (deltaRow = -1; deltaRow <=1; deltaRow++) {//flips the first right direction and not the rest
		for (deltaCol = -1; deltaCol<=1; deltaCol++) {
			legalFlip = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
			if (legalFlip) {
				for (int i=row+deltaRow, j=col+deltaCol; board[i][j] != colour; i+=deltaRow, j+=deltaCol) {
					score++;
				}
			}
		}
	}
	
	return score;
}

char identifyWinner(char board[][26], int n) {
	int row, col;
	int U, W, B;
	
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			if (board[row][col] == 'W') W++;
			else if (board[row][col] == 'B') B++;
			else U++;
		}
	}
	
	if (W > B) return 'W';
	else if (B > W) return 'B';
	else return 'U';
}

bool gameOver(char board[][26], int n) {
	int count = 1, unoccupiedCount = 0, row, col, deltaRow, deltaCol;
	char colour;
	bool legal, legalW, legalB;
	
/*	while (count>=0) {
		if (count == 1) colour = 'W';
		else colour = 'B';
		
		for (row = 0; row < n; row++) {//row increment
			for (col = 0; col < n; col++) {//col increment
				for (deltaRow = -1; deltaRow <=1; deltaRow++) {//flips the first right direction and not the rest
					for (deltaCol = -1; deltaCol<=1; deltaCol++) {
						if (count == 1) {
							legalW = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
						} else {
							legalB = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
						}
						if (legalW || legalB) break; //at least one move available, so break
					}
				if (legalW || legalB) break;
				}
			}
		}
		
		if (legalW == false && legalB == false) return true; //no moves available so return true for gameover
		else return false;
		count--;
	}*/
	// checking if any legal moves available for white - loop breaks if move is available, true
	colour = 'W';
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			for (deltaRow = -1; deltaRow <=1; deltaRow++) {//flips the first right direction and not the rest
				for (deltaCol = -1; deltaCol<=1; deltaCol++) {
					legalW = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
					if (legalW) break; //at least one move available, so break
				}
			if (legalW) break;
			}
		}
	}
	
	// checking if any legal moves available for black - loop breaks if move is available, true
	colour = 'B';
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			for (deltaRow = -1; deltaRow <=1; deltaRow++) {//flips the first right direction and not the rest
				for (deltaCol = -1; deltaCol<=1; deltaCol++) {
					legalB = checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol);
					if (legalB) break; //at least one move available, so break
				}
			if (legalB) break;
			}
		}
	}
	
	//return false when game is not over
	//return true when game is over
	
	if (legalW == true && legalB == true) return false; //false: game is 
	else if (legalW == false && legalB == false) return true;
	
	for (row = 0; row < n; row++) {//row increment
		for (col = 0; col < n; col++) {//col increment
			if (board[row][col] == 'U') unoccupiedCount++;
		}
	}
	
	if (unoccupiedCount == 0) return false; //0 spaces are unoccupied, meaning game is over
}