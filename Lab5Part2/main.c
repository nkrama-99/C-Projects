#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

int rollDice (void) {//returns the sum of 2 random numbers
	int rand1 = (rand() % 6) + 1;
	int rand2 = (rand() % 6) + 1;
	return rand1+rand2;
}

bool playGame(void) { //play game, return true if win, display results
	int sum1, sum2;
	sum1 = rollDice();
	printf("You rolled: %d \n", sum1);
	
	if (sum1 == 7 || sum1 == 11){
		printf("You win! \n");
		return true;
	} else if (sum1 == 2 || sum1 == 3 || sum1 == 12){
		printf("You lose! \n");
		return false;
	} else {
	
	printf("Your point is: %d \n", sum1);
	do {
		sum2 = rollDice();
		printf("You rolled: %d \n", sum2);
		if (sum2 == 7){
		printf("You lose! \n");
		return false;
		}
	} while (sum2!=sum1); //exits loop when sum2 == sum1
		
		printf("You win! \n");
		return true;
	}
}

void winLoss(void) //track and print no of wins and losses, repeatedly calls playGame until stop request from user 
{
	int wins=0, losses=0;
	char rematch;
	bool result;
	
	do {
		result = playGame();
		if (result == true) {
			wins++;
		} else {
			losses++;
		}
		
		printf("Play again? ");
		scanf(" %c", &rematch);
	} while (rematch == 'Y' || rematch == 'y');
	
	printf("\nWins: %d \n", wins);
	printf("Losses: %d \n", losses);
	return;
}



int main(int argc, char **argv)
{
	time_t t;
	srand((unsigned) time(&t));
	winLoss(); //calls playgame (which calls rolldice)
}
