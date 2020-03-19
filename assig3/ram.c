/* Kernel written by Sabina Sasu, 260803977*/
/* ECSE427 Mcgill Winter 2020 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ram[40];
int m = 0;
int RAMsize = 40;
int page = 4;

char* getRAM(int k){
	return strdup(ram[k]);
}

void initiateRAM(){
	for(int i = 0; i < RAMsize; i++){
		ram[i] = NULL;
	}
}

void cleanUpRAM(){
	for(int i = 0; i < m; i++){
		ram[i] = NULL;
	}
	m=0;
}

void printRAM(){
	printf("%d\n", m);
	for(int i = 0; i < m; i++){
		printf("%d %s\n", i, ram[i]);
	}
}

void printAllRAM(){
	//printf("%d\n", m);
	for(int i = 0; i < RAMsize; i++){
		printf("%d %s\n", i, ram[i]);
	}
}

void loadPageRAM(int frame, char *fInput){
	int f = frame*page;
	printf("Loading: %s\n", fInput);	
	for(int i = f-page; i < f; i++){
		if(ram[i] == NULL){
			ram[i] = strdup(fInput);
			break;
		}
	}
}

int getNextFrame(){
	for(int i = 0; i < RAMsize/page; i++){
		if(ram[i*page] == NULL){
			return i+1;
		}
	}
	return -1;
}

//add the source code to the next available cells in ram[].
int addToRAM(FILE *p, int *start, int *end){
	int * m1 = &m;
	*start = *m1;
	char fInput[1000];
	//iterate through file and add lines in ram, increment n
	fgets(fInput, 999, p);
	while(!feof(p)) {
		ram[m] = strdup(fInput);
		m++;
		if(m >= 40){
			printf("Ram space is full, aborting\n");
			cleanUpRAM();
			return 4;
		}
		fgets(fInput, 999, p);
	}

	fclose(p);
	int * m2 = &m;
	*end = *m2;
	//printf("Start %d, End %d, m %d\n", *start, *end, m);
	return 0;
}


