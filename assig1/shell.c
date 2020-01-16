/*
 * shell.c
 *
 *  Created on: Jan 16, 2020
 *      Author: Bubble
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char prompt[100] = {'$', '\0'};  //can be modified
	char userInput[1000];            //user input stored here
	int errorCode = 0;               //0 means no error, default
	char name[30] = "Sabina";
	printf("Welcome to the %s shell! \n", name);
	printf("Version 1.0 Created January 2020\n");
	while(1) {
		printf("%s", prompt);
		fgets(userInput, 999, stdin); //limit input to size array

		errorCode = parse(userInput);

		if(errorCode == -1)
			exit(99); //ignore all other errors
		else if(errorCode == 1)
			printf("Unknown command\n");

	}

}

int parse(char input[]){
	char tmp[200];
	char *words[100];
	int a;
	for(a=0; input[a]==' ' && a<1000; a++); //skip first white spaces

	while(input[a] != '\0' && a<1000) {
		int b, w = 0;
		for(b=0; input[a]!='\0' && input[a]!=' ' && a<1000; a++, b++)
			tmp[b] = input[a]; //extract a word

		tmp[b] = '\0';
		words[w] = strdup(tmp); //using stringdup to copy string
		a++; w++;
	}

	return interpreter(words); //assumes cmd switches args


}
