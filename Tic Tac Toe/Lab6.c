#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void printBoard(int board[], int playerA, int playerB) {
	for(int i=0; i<9; i+=3) {//for rows
		for(int j=0; j<3; j++) {//for columns
			if (board[i+j] == playerA) printf(" A");
			else if (board[i+j] == playerB) printf(" B");
			else printf(" %d", board[i+j]);
		}
		printf("\n");//next line after one row is completed
	}
	printf("\n");//after the entire board is printed
}

int requestValidInput(int board[], int playerA, int playerB) {
	int playerInput = 0;
	printf("Please enter a valid position to play.\n");
	
	do{
		scanf("%d", &playerInput);
		if (playerInput<1 || playerInput>9) {//input is out of range
			printf("Invalid input, please try again.\n");
		} else if (board[playerInput-1] == playerA || board[playerInput-1] == playerB) {//input is already occupied
			printf("That position has already been played, please try again.\n");
		}
	} while (playerInput<=0 || playerInput>9 || board[playerInput-1] == playerA || board[playerInput-1] == playerB);
	
	return playerInput;
}

int checkForWinner(int board[], int playerA, int playerB) {
	int winnerIdentity = 999, draw = 0;
	
	if (board[0] == board[3] && board[3] == board[6]){//case 1: Vertical victory
		winnerIdentity = board[0];
	} else if (board[1] == board[4] && board[4] == board[7]){
		winnerIdentity = board[1];
	} else if (board[2] == board[5] && board[5] == board[8]){
		winnerIdentity = board[2];
	} else if (board[0] == board[1] && board[1] == board[2]){//case 2: Horizontal victory
		winnerIdentity = board[0];
	} else if (board[3] == board[4] && board[4] == board[5]){
		winnerIdentity = board[3];
	} else if (board[6] == board[7] && board[7] == board[8]){
		winnerIdentity = board[6];
	} else if (board[0] == board[4] && board[4] == board[8]){//case 3: Cross victory
		winnerIdentity = board[0];
	} else if (board[2] == board[4] && board[4] == board[6]){//case 4: Cross Victory
		winnerIdentity = board[2];
	}
	//case 5: entire board occupied and no winner
	else if ((board[1] == playerA || board[1] == playerB) &&
	(board[2] == playerA || board[2] == playerB) &&
	(board[3] == playerA || board[3] == playerB) &&
	(board[4] == playerA || board[4] == playerB) &&
	(board[5] == playerA || board[5] == playerB) &&
	(board[6] == playerA || board[6] == playerB) &&
	(board[7] == playerA || board[7] == playerB) &&
	(board[8] == playerA || board[8] == playerB)) {
		winnerIdentity = draw; //signifies draw
	}
	//if none applies
	else {
		winnerIdentity = 999; //999 signifies no winner -- prompts game to continue (main loop only ends when winnerIdentity is draw, playerA or playerB
	}
	return winnerIdentity;
}

int main(void) {
	int board[9] = {1,2,3,4,5,6,7,8,9};
	int playerA = 100, playerB = 200, draw = 0;
	int currentPlayer=1, boardLocation, winnerIdentity = 999;
	
	printf("The current state of the Tic-tac-toe Board: \n\n");
	printBoard(board, playerA, playerB);
	
	do {
		if (currentPlayer%2 != 0) {//defines player A
			printf("It is Player A's turn.\n");
			boardLocation = requestValidInput(board, playerA, playerB);
			board[boardLocation-1] = playerA; //boardLocation is always 1 more than the index being reffered to
			winnerIdentity = checkForWinner(board, playerA, playerB);
			currentPlayer++;
			if (winnerIdentity != playerA && winnerIdentity != draw) {
				printf("The current state of the Tic-tac-toe Board: \n\n");
				printBoard(board, playerA, playerB);
			}
		} else {//defines player B
			printf("It is Player B's turn.\n");
			boardLocation = requestValidInput(board, playerA, playerB);
			board[boardLocation-1] = playerB; //boardLocation is always 1 more than the index being reffered to
			winnerIdentity = checkForWinner(board, playerA, playerB);
			currentPlayer++;
			if (winnerIdentity != playerB && winnerIdentity != draw) {
				printf("The current state of the Tic-tac-toe Board: \n\n");
				printBoard(board, playerA, playerB);
			}
		}
	} while (winnerIdentity != draw && winnerIdentity != playerA && winnerIdentity != playerB); //loops till winnerIdentity is playerA, playerB or draw) 
	
	if (winnerIdentity == playerA){
		printf("Player A wins!\n");
	} else if (winnerIdentity == playerB){
		printf("Player B wins!\n");
	} else if (winnerIdentity == draw){
		printf("It's a draw!\n");
	}

	printf("\n");
	printBoard(board, playerA, playerB);
	return 0;
}
