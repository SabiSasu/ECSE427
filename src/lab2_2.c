/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
	char name[30];
	int age;
	double gpa;
}*array;

int main()
{
	int size;
	printf("Enter an array size: ");
	scanf("%d", &size);
	array = malloc(size * sizeof(*array));

	// if memory cannot be allocated
	if(array == NULL)
	{
		printf("Error! memory not allocated.");
		exit(0);
	}

	int n = 0;
	printf("Enter a cell number between %d-%d: ", 0, size-1);
	scanf("%d", &n);
	if(n < 0 || n >  size-1)
	{
		printf("Number must be between bounds, program aborted");
		exit(0);
	}

	char name[30];
	int age;
	double gpa;
	printf("Enter a name, age and gpa: ");
	scanf("%s%d%lf", name, &age, &gpa);
	strcpy(array[n].name, name);
	array[n].age = age;
	array[n].gpa = gpa;
	printf("New entry saved: ");
	printf("%s, %d, %lf", array[n].name, array[n].age, array[n].gpa);
	free(array);

}
