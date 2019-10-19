#include <stdio.h>

void inputDate(int *day, int *month, int *year){
	printf("Please enter a date: ");
	scanf("%d/%d/%d", day, month, year);
}

void calculateDay(int day, int month, int year){
	//algorithm definitions
	int B = day; //day of the month
	
	int C, D;
	
	int A; //A is the month, but first month is march
	if (month>=3) {
		A = month - 2;
		C = year%100;
		D = year/100;
	} else {
		A = month + 10;
		int yearTemp = year - 1;
		C = yearTemp%100;
		D = yearTemp/100;
	}
	
	//algorithm begins
	int W = (13*A - 1) / 5;
	int X = C / 4;
	int Y = D / 4;
	int Z = W + X + Y + B + C - 2*D;
	int R = Z % 7;
	if (R<0){
		R = R + 7;
	}
	
	printf("The day %d/%d/%d is a ", day, month, year);
	if (R == 0) {printf("Sunday. \n");}
	if (R == 1) {printf("Monday. \n");}
	if (R == 2) {printf("Tuesday. \n");}
	if (R == 3) {printf("Wednesday. \n");}
	if (R == 4) {printf("Thursday. \n");}
	if (R == 5) {printf("Friday. \n");}
	if (R == 6) {printf("Saturday. \n");}
	
	return;
}

int main(int argc, char **argv)
{
	int day, month, year;
	inputDate(&day, &month, &year);
	calculateDay(day, month, year);
	return 0;
}
