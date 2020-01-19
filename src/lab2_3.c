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
	struct Student *next;
}*head = NULL;


void push(char name[], int age, double gpa){
	struct Student* temp = (struct Student*)malloc(sizeof(struct Student));
	strcpy(temp.name, name);
	temp.age = age;
	temp.gpa = gpa;
	temp.next = head;
	head = temp;
}

struct Student* pop(){
	struct Student* temp = head;
	//new head is next element
	head = temp.next;
	//return popped element
	return temp;

}

int main()
{
	char userInput[1000] = "y";            //user input stored here

	do{
		char name[30];
		int age;
		double gpa;
		printf("Enter a name, age and gpa: ");
		scanf("%s%d%lf", name, &age, &gpa);
		push(name, age, gpa);

		printf("Press y to keep adding students: ");
		fgets(userInput, 1, stdin);
	}while((strcmp(userInput, "y") == 0 || strcmp(userInput, "Y") == 0 ));


	printf("Your students are:\n");
	while(head != NULL){
		struct Student* temp = pop();
		printf("%s, %d, %lf\n", temp.name, temp.age, temp.gpa);
		free(temp);
	}



}
