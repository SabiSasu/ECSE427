/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>


int factorial(int n){
	if(n == 1)
		return n;
	else
		return n* factorial(n-1);

}

int part1(){
	int number;
	char name[500];
	printf("Enter a number: ");
	scanf("%d", &number);
	int n = factorial(number);
	printf("result: %d", n);

}


int main()
{
    part1();
}
