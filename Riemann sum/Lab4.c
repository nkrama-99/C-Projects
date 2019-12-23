//this code works and exercise gives 3/3, updated on 2/6/19
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool validateInput(double validateLeftBound, double validateRightBound, int validateNumberRect) {//when called returns true or false
	if (validateLeftBound<-10.0 || validateRightBound>10.0 || validateRightBound<=validateLeftBound || validateNumberRect <= 0) {
		printf("Invalid inputs... \n");
		printf("\n");
		return false;
	} else {
		return true;
	}
}

double evalFunc(double x) {//when called returns height of the rectangle
	//double rectHeight;
	//rectHeight = 2*pow(x,2) - 7*x - 2;
	return 2*pow(x,2) - 7*x - 2;
}

int main(int argc, char **argv) {
	int numberRect;
	double leftBound, rightBound, stepSize;
	double leftPoint=0, rightPoint=0, midPoint=0;
	
	do {//runs code once before looping until function returns true (inputs met conditions)
		printf("Enter the Left boundary: a, Right boundary: b, and No. of rectangles to use. \n");
		printf("To exit enter 0 0 0 \n");
		scanf("%lf %lf %d", &leftBound, &rightBound, &numberRect);
		
		if (leftBound==0 && rightBound==0 && numberRect==0) {//exits program when 0 0 0 entered
			printf("Invalid inputs... \n");
			printf("\n");
			printf("Terminating main! \n");
			return 0;
		}
	} while (!validateInput(leftBound, rightBound, numberRect));
	
	stepSize = (rightBound - leftBound) / numberRect; //stepsize is the width(base) of the rectangle
	
	//for loops accumulate the area of rectangles: stepSize*rectHeight
	for (int i = 0; i<=numberRect-1; i++){//computing left riemanns
		leftPoint = leftPoint + stepSize*evalFunc(leftBound + i*stepSize);
	}
	for (int i = 1; i<=numberRect; i++){//computing right riemanns
		rightPoint = rightPoint + stepSize*evalFunc(leftBound + i*stepSize);
	}
	for (int i = 0; i<=numberRect-1; i++){//computing mid riemanns
		midPoint = midPoint + stepSize*evalFunc(leftBound + stepSize/2 + i*stepSize);
	}
	
	printf("With Step Size: %.4lf \n", (rightBound - leftBound)/numberRect);
	printf("The approximate integral of the f(x) = 2(x^2)-7x-2 \n");
	printf("Bound between %.2lf and %.2lf, using %d rectangles is as follows \n", leftBound, rightBound, numberRect);
	printf("\n");
	printf("Mid point evaluation approximate: %.4lf \n", midPoint);
	printf("Left point evaluation approximate: %.4lf \n", leftPoint);
	printf("Right point evaluation approximate: %.4lf \n", rightPoint);
	
	return 0;
}