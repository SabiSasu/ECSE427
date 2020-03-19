/* Shell written by Sabina Sasu, 260803977*/
/* ECSE427 Mcgill Winter 2020 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEM_LENGTH 100
struct MEM {
	char *var;
	char *value;
}shellMem[MEM_LENGTH]; //=  malloc(1000 * sizeof(*shellMem));
int n = 0;

void shell_memory_initialize()
{
    for (size_t i = 0; i < MEM_LENGTH; ++i)
    {
        shellMem[i].var = NULL;
        shellMem[i].value = NULL;
    }
}

void shell_memory_destory()
{
    for (size_t i = 0; i < MEM_LENGTH; ++i)
    {
        if (shellMem[i].var != NULL)
            free(shellMem[i].var);
        if (shellMem[i].value != NULL)
            free(shellMem[i].value);
    }
}

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
	if(n < MEM_LENGTH){
		shellMem[n].value = strdup(value);
		shellMem[n].var = strdup(var);
		n++;
	}
	else{
		printf("memory is full, aborting\n");
		return -1;
	}

	return 0;
}

char* getVar(char var[]){
	for(int i = 0; i < n; i++){
		if(strcmp(shellMem[i].var, var) == 0)
			return shellMem[i].value;
	}
	return "\0";
}






