/* Shell written by Sabina Sasu, 260803977*/
/* ECSE427 Mcgill Winter 2020 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "shellmemory.h"
#include "shell.h"

int shellUI(){
	char prompt[100] = {'$', '\0'};
	char userInput[1000];
	int errorCode = 0;
	char name[30] = "Sabina";
	shell_memory_initialize();
	printf("Welcome to the %s shell! \n", name);
	printf("Version 2.0 Updated February 2020\n");
	while(1) {
		printf("%s", prompt);
		fgets(userInput, 999, stdin); //limit input to size array
		errorCode = parse(userInput);

		if(errorCode == -1)
			exit(99);
		else if(errorCode == 1)
			printf("Unknown command\n");
		else if(errorCode == 2)
			printf("Variable does not exist\n");
		else if(errorCode == 3)
			printf("Script not found\n");
		else if(errorCode == 4)
			printf("Wrong number of arguments\n");
		else if(errorCode == 5)
			printf("Script not found\n");
	}

	shell_memory_destory();
	return 0;
}

int parse(char input[]){
	char tmp[200];
	char *words[100];
	int a;
	for(a=0; input[a]==' ' && a<1000; a++); //skip first white spaces

	int w = 0;
	while(input[a] != '\0' && a<1000) {
		int b = 0;

		for(b=0; input[a]!='\0' && input[a]!=' ' && a<1000; a++, b++){
			//removing the line return
			if(input[a] != '\n' && input[a]!= '\r')
				tmp[b] = input[a];
			else
				break;
		}
		//deals with trailing spaces
		if(b > 0){
			tmp[b] = '\0';
			words[w] = strdup(tmp); //using stringdup to copy string
			w++;
		}
		 a++;
	}
	//declaring end of words
	words[w] = "/0";
	int i = 0;
	return interpreter(words);


}
