#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ram.h"
#include "pcb.h"
#include "kernel.h"
int pageSize = 4;
static int m = 1;

int findFrame() {
    int frame = getNextFrame();
    return frame;
}

int findVictim(struct PCB *p){
    return 0;
}

int updatePageTable(struct PCB *p, int pageNumber, int frameNumber, int victimFrame){
    return 0;
}

void loadPage(int pageNumber, FILE *f, int frameNumber){
    int lines = 0;
    int thresh = pageNumber * pageSize;
    char fInput[1000];
	fgets(fInput, 999, f);
	while(!feof(f)){
	  
	  lines++;
	  //line is within page, add to ram
	  if(lines <= thresh && lines >= thresh-pageSize){
	    loadPageRAM(frameNumber, fInput);
	  }
	  
	  fgets(fInput, 999, f);
	}
}

int countTotalPages(FILE *f){
	int lines = 0;
	char fInput[1000];
	fgets(fInput, 999, f);
	while(!feof(f)){
	   lines++;
	   fgets(fInput, 999, f);
	}
	printf("Numb Lines: %d\n", lines);
	int a = (lines + pageSize - 1) / pageSize; 
	return a;
}

int launcher(FILE *p){
	int err = 0;
	//1. copy file in BackingStore
	char fInput[1000];
	char fileName [1000]= "BackingStore/";
	strcat(fileName, fileNameExec);
	FILE * target;
	target = fopen(fileName, "w+");
	if(target == NULL){
      fclose(p);
      printf("Cant create a file in BackingStore, aborting...\n");
      return -4;
    }
    fgets(fInput, 999, p);
	while(!feof(p)){
	  fputs(fInput, target);
	  fgets(fInput, 999, p);
	}
	//2. close file pointers
	fclose(p);
	fclose(target);
	
	//3. open file in BackingStore
	FILE * backFile = fopen(fileName, "r");
	if(target == NULL){
      fclose(backFile);
      printf("Cant open the file in the BackingStore, aborting...\n");
      return -4;
    }
	
	//4.a.get total pages
	int countPages = countTotalPages(backFile);
	printf("Numb Pages: %d\n", countPages);
	rewind(backFile);
	
	//5.b. Load only 2 pages of it
	
	/*
	loadPage(3, p, 1);
	printAllRAM();
	int a = findFrame();
	printf("next frame: %d\n", a);
	if(a==-1){
	    //findVictim();
	}
	*/
	return err;
}
