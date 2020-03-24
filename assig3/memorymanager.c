#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ram.h"
#include "pcb.h"
#include "kernel.h"

int pageSize = 4;

int findFrame() {
    int frame = getNextFrame();
    return frame;
}

int findVictim(struct PCB *p){
    int randomnumber = rand() % 10;
    printf("%d\n", randomnumber);
    //iterate pcb page table
    for(int i = 0; i < p->pages_max; i++){
       //if the frame exists in the pagetable, get next number and reset loop
        if(p->pageTable[i] == randomnumber){
            if (randomnumber < 9)
                randomnumber++;
            else
                randomnumber=0;
            i=0;
         }
    }
    
    //if all good, clear the frame
    clearFrame(randomnumber);
    return randomnumber;
}

void loadPage(int pageNumber, FILE *f, int frameNumber){
    int lines = 0;
    int thresh = pageNumber * pageSize;
    char fInput[1000];
	fgets(fInput, 999, f);
	while(!feof(f)){
	  
	  //line is within page, add to ram
	  if(lines >= thresh && lines < thresh+pageSize){
	    loadPageRAM(frameNumber, fInput);
	  }
	  lines++;
	  fgets(fInput, 999, f);
	}
}

int updatePageTable(struct PCB *p, int pageNumber, int frameNumber, int victimFrame){
    int err = 0;
    if(frameNumber != -1){
        p->pageTable[pageNumber] = frameNumber;
    }
    else{
        p->pageTable[pageNumber] = victimFrame;
        err = updateVictimPageTable(victimFrame);   
    }
    
    return err;
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
	int err = 1;
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
	if(countPages > 10){
	    printf("Cannot launch a program with %d pages\n", countPages);
	    return 0;
	}
	
	//create pcb
	struct PCB *this = malloc (sizeof (struct PCB));
	 strcpy(this->fileName, fileName);
	this->pages_max=countPages;
	this->PC=0;
	this->PC_offset=0;
	this->PC_page=0;
	//this->pageTable[0] = malloc(sizeof(int) * 10);
	for(int i = 0; i < countPages; i++)
	    this->pageTable[i] = NULL;
	printf("%s\n", this->fileName);
	
	//5.b. Load only 2 pages of it
	for(int a = 0; a < countPages && a < 2; a++){
	    //5.c. Get frame
	    int frame = findFrame();
	    int victimFrame = -1;
	    printf("next frame: %d, page: %d\n", frame, a);
	    //5.d. Get victim frame if get frame fails
	    if(frame==-1){
	        victimFrame = findVictim(this);
	        loadPage(a, backFile, victimFrame);
	    }
	    else
	        loadPage(a, backFile, frame);
	    
	    rewind(backFile);
	    //5.e. update page table
	    updatePageTable(this, a, frame, victimFrame);
	}
	
	//update PC, PC_page and PC_offset
	this->PC_page = 1;
	this->PC = (this->pageTable[0] * pageSize) + this->PC_offset;
	
	//add to ready queue 
	addToReady(this);
	printf("\n");
	printAllRAM();
	fclose(backFile);
	return err;
}
