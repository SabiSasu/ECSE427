/*
 * shellmemory.c
 *
 *  Created on: Jan 16, 2020
 *      Author: Bubble
 */

/*struct SHELLMEMORY {
   char *variable;
   char *value;
   struct SHELLMEMORY *next;
} *shellMemory = NULL;
*/

int help(char *words[]){
	printf("%-20s%s\n", "COMMAND", "DESCRIPTION");
	printf("%-20s%s\n", "help", "Displays all the commands");
	printf("%-20s%s\n", "quit", "Exits / terminates the shell with ""Bye!""");
	printf("%-20s%s\n", "set VAR STRING", "Assigns a value to shell memory");
	printf("%-20s%s\n", "print VAR", "Displays the STRING assigned to VAR");
	printf("%-20s%s\n", "run SCRIPT.TXT", "Executes the file SCRIPT.TXT ");
	printf("\n");
	return 0;
}

int quit(char *words[]){
	printf("Bye!");
	exit(99);
	return 0;
}

int set(char *words[]){
	int errcode = 0;
	//checks to see if variable exist

	//otherwise returns error code 2
	return errcode;
}

int print(char *words[]){
	int errcode = 0;
	//checks to see if variable exist

	//otherwise returns error code 2
	return errcode;
}

int run(char *words[]){
	return 0;
}


