/* Shell written by Sabina Sasu, 260803977*/
/* ECSE427 Mcgill Winter 2020 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shellmemory.h"
#include "interpreter.h"
#include "shell.h"
#include "pcb.h"
#include "kernel.h"
#include "ram.h"
#include "memorymanager.h"


//checks if input has the correct amount of args
int checkArray(int m, char *words[]){
	int match = 0;
	for(int i = 1; i <= m+1; i++){
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

//checks if name files are the same
int checkFileName(char *words[], int n){
	int err = 0;
	switch(n){
	case 1: break;
	case 2:
		if(strcmp(words[n], words[n-1]) == 0){
			printf("Error: Script %s already loaded\n", words[n]);
			err=4; } break;
	case 3: if(strcmp(words[n-2], words[n]) == 0){
		printf("Error: Script %s already loaded\n", words[n]);
		err=4; break;
	}
	else if (strcmp(words[n], words[n-1]) == 0){
		printf("Error: Script %s already loaded\n", words[n]);
		err=4; break;
	}
	else if ((strcmp(words[n-1], words[n-2]) == 0)){
		printf("Error: Script %s already loaded\n", words[n-1]);
		err=4; break;
	}
	}
	return err;
}


int exec(char * words[]){
	int errcode = 0;
	int check1 = checkArray(1, words);
	int check2 = checkArray(2, words);
	int check3 = checkArray(3, words);
	int n = check1+(check2*2)+(check3*3);
	//check there is at least one argumen and max 3
	if(n==0){
		errcode = 4;
	}
	else{
		//int errcode = checkFileName(words, n);
		//returns errcode 4 of file name appears more than once (assig2 only)
		int i = 1;
		while(errcode != 4 && i <= n){
			//open all the files
			errcode = myinit(words[i]);
			i++;
			
		}
		if(errcode != 4){
			//printQueue();
			//printRAM();
			int a = scheduler();
		}
		else{
			
		}
	}
	return errcode;
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
		printf("%-20s%s\n", "run SCRIPT.TXT", "Executes the file SCRIPT.TXT");
		printf("%-20s%s\n", "exec p1 p2 p3", "Executes concurrent programs");
		printf("\n");
	}
	return errcode;
}

int quit(char *words[]){
	int errcode = 0;
	int check = checkArray(0, words);
	if(check == 0){
		errcode = 4;
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
		errcode = 4;
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
		errcode = 4;
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
		errcode = 4;
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
					f=NULL;
					errcode = 0;
					break;
				}
				fgets(fInput, 999, f);
			}
			if(f!=NULL)
			fclose(f);
		}
		else{
			errcode = 3;
		}
	}
	//return error msh if cant open file
	return errcode;
}


int interpreter(char *words[]) {
	int errCode = 0;

	//The user is asking to execute a single command
	if (strcmp(words[0], "help") == 0)        errCode = help(words);
	else if (strcmp(words[0], "quit") == 0)   errCode = quit(words);
	else if (strcmp(words[0], "set") == 0)    errCode = set(words);
	else if (strcmp(words[0], "print") == 0)  errCode = print(words);
	else if (strcmp(words[0], "run") == 0)    errCode = run(words);
	else if (strcmp(words[0], "exec") == 0)   errCode = exec(words);
	else errCode = 1;

	return errCode;
}

