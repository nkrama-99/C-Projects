#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void input(int *num)
{
	do {
		printf("Please enter an integer greater than 99999: ");
		scanf("%d", num); //scanf to address replaces what is in the location **NOTE: its not &num, because num is the address
		if (*num<=99999) {
			printf("Incorrect input. \n");
		}
	} while (*num<=99999);
	printf("The number entered is %d \n", *num);
	return;
}

int add4(int num)
{
	//Finding the number of digits in num WORKING
	int i = 1;
	
	int test = num/(10);
	while (test!=0){
		test = num/(pow(10,i));
		i++;
	}
	int digits = i-1;
	
	//Algortith to breakdown int to array
	int numArray [digits];
	
	for (int k=0; k<=digits-1; k++) {
		numArray[k] = num % (int)pow(10,digits-k);
	}
	
	for (int j=0; j<=digits-1; j++) {
		numArray[j] = numArray[j] / (int)pow(10,digits-j-1);
	} //algortithm ends
	
	//adding 4 to arrays
	for (int l=0; l<=digits-1; l++) {
		if (numArray[l]>=6){
			numArray[l] = numArray[l] + 4 -10;
		} else {
			numArray[l] = numArray[l] + 4;
		}
	}
	
	//algorithm to convert back to int
	int numNew = 0;
	for (int m=0; m<=digits-1; m++) {
		numNew = numNew + numArray[m] * pow(10, digits-m-1);
	} //algorith ends
	
	return numNew;
}

int shift(int num)
{
	//Finding the number of digits in num WORKING
	int i = 1;
	
	int test = num/(10);
	while (test!=0){
		test = num/(pow(10,i));
		i++;
	}
	int digits = i-1;
	
	//Algortith to breakdown int to array
	int numArray [digits];
	for (int k=0; k<=digits-1; k++) {
		numArray[k] = num % (int)pow(10,digits-k);
	}
	
	for (int j=0; j<=digits-1; j++) {
		numArray[j] = numArray[j] / (int)pow(10,digits-j-1);
	} //algortithm ends
	
	//swapping positions
	int l=0, temp;
	temp = numArray[l];
	for (l=0; l<=digits-1; l++) {
		if (l==digits-1) {
			numArray[l] = temp;
		} else {
		numArray[l] = numArray[l+1];
		}
	}
	
	//algorithm to convert back to int
	int numNew = 0;
	for (int m=0; m<=digits-1; m++) {
		numNew = numNew + numArray[m] * pow(10, digits-m-1);
	} //algorith ends
	
	return numNew;
}

void printOutput(int encryptNum, int originalNum)
{
	printf("Original number: %d \n", originalNum);
	printf("Encrypted number: %d \n", encryptNum);
	return;
}

int main(int argc, char **argv)
{
	int reference;
	input(&reference);
	printOutput(shift(add4(reference)),reference);
}
