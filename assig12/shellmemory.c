/* Shell written by Sabina Sasu, 260803977*/
/* ECSE427 Mcgill Winter 2020 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

struct MEM {
	char *var;
	char *value;
}shellMem[1000]; //=  malloc(1000 * sizeof(*shellMem));
int n = 0;

char* overwrite(char name[], char value[]){
	for(int i = 0; i < n; i++){
		if(strcmp(shellMem[i].var, name) == 0){
			shellMem[i].value = value;
			return shellMem[i].value;
		}

	}
	return "/0";
}

int add(char var[], char value[]){
	shellMem[n].value = strdup(value);
	shellMem[n].var = strdup(var);
	n++;
	return 0;
}

char* getVar(char var[]){
	for(int i = 0; i < n; i++){
		if(strcmp(shellMem[i].var, var) == 0)
			return shellMem[i].value;
	}
	return "\0";
}

int checkArray(int m, char *words[]){
	int match = 0;
	for(int i = 1; i <= m+1; i++){
		//printf("%d, %d, %s\n", i, n, words[i]);
		if(strcmp(words[i], "/0") == 0){
			if(i == m+1){
				match = 1;
				return match;
			}
			//reached end but not n
			break;
		}
	}
	return match;
}

int help(char *words[]){
	int errcode = 0;
	int check = checkArray(0, words);
	if(check == 0){
		errcode = 1;
	}
	else{
		printf("%-20s%s\n", "COMMAND", "DESCRIPTION");
		printf("%-20s%s\n", "help", "Displays all the commands");
		printf("%-20s%s\n", "quit", "Exits / terminates the shell with ""Bye!""");
		printf("%-20s%s\n", "set VAR STRING", "Assigns a value to shell memory");
		printf("%-20s%s\n", "print VAR", "Displays the STRING assigned to VAR");
		printf("%-20s%s\n", "run SCRIPT.TXT", "Executes the file SCRIPT.TXT ");
		printf("\n");
	}
	return errcode;
}

int quit(char *words[]){
	int errcode = 0;
	int check = checkArray(0, words);
	if(check == 0){
		errcode = 1;
	}
	else{
		printf("Bye!\n");
		errcode = -1;
	}
	return errcode;
}

int set(char *words[]){
	int errcode = 0;
	int check = checkArray(2, words);
	if(check == 0){
		errcode = 1;
	}
	else{
		//checks to see if variable exist
		char *found = overwrite(words[1], words[2]);
		if(strcmp(found, "/0") == 0){
			errcode = add(words[1], words[2]);
		}
	}
	return errcode;
}

int print(char *words[]){
	int errcode = 0;
	int check = checkArray(1, words);
	if(check == 0){
		errcode = 1;
	}
	else{
		char * value = getVar(words[1]);
		if(strcmp(value, "\0") != 0){
			printf("%s = %s\n", words[1], value);
		}
		else{
			errcode = 2;
		}
	}
	return errcode;
}

int run(char *words[]){
	int errcode = 0;
	int check = checkArray(1, words);
	if(check == 0){
		errcode = 1;
	}
	else{
		char fInput[1000];
		FILE *f = fopen(words[1], "r");
		//only read file if could open succesfully
		if(f != NULL){
			//reading lines
			fgets(fInput, 999, f);
			while(!feof(f)) {
				errcode = parse(fInput); //which calls interpreter()
				if (errcode < 0) {
					fclose(f);
					errcode = 0;
					break;
				}
				fgets(fInput, 999, f);
			}
			fclose(f);
		}
		else{
			errcode = 3;
		}
	}
	//return error msh if cant open file
	return errcode;
}


