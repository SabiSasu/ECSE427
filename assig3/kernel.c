/* kernel.cp written by Sabina Sasu, 260803977*/
/* ECSE427 Mcgill Winter 2020 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "shell.h"
#include "ram.h"
#include "pcb.h"
#include "cpu.h"
#include "memorymanager.h"


static int lock = 0; 
int getLock() 
{ 
  lock++;
  return lock; 
} 

void resetLock(){
    lock = 0;
}

struct RQNode{
	struct PCB pcb;
	struct RQNode *next;
};
struct RQNode *head, *tail;
char *fileNameExec;

void boot(){
	//initiate all ram slots to NULL
	initiateRAM();
	
	//delete directory if it exists (to avoid error messages)
	DIR* dir = opendir("BackingStore");
	if (dir) {
   		system("rm -r BackingStore");
	}
	//create a new directory
   	system("mkdir BackingStore");
}

int kernel(){
	printf("Kernel 2.0 loaded!\n");
	shellUI();
}

int main(){
	int error=0; 
	boot(); // First : actions performed by boot 
	error = kernel(); // Second: actions performed by kernel 
	return error; 
}

// add the PCB to the tail of the Ready Queue
void addToReady(struct PCB *new_pcb){
	struct RQNode *new;
	new = (struct RQNode*)malloc(sizeof(struct RQNode));
	new->pcb = *new_pcb;
	new->next=NULL;
	printf("PCB added: PC %d, offset %d, page %d\n", new->pcb.PC, new->pcb.PC_offset, new->pcb.PC_page);
	if(head == NULL){
		head = (struct RQNode*)malloc(sizeof(struct RQNode));
		tail = (struct RQNode*)malloc(sizeof(struct RQNode));
		//new pcb is both head and tail
		head = new;
		tail = new;
	}
	else{
		//append new pcb to tail, now tail is new pcb
		struct RQNode *temp = tail;
		tail->next = new;
		tail = new;
	}
}

void printQueue(){
printf("Printing PCB queue.\n");
	int i = 0;
	struct RQNode *t;

	t = head;

	if (t == NULL) {
		printf("Linked list is empty.\n");
		return;
	}
	printf("printint queue\n");
	while (t->next != NULL) {
		printf("PCB %d: PC %d, Current page %d, Offset %d\n", i, t->pcb.PC, t->pcb.PC_page, t->pcb.PC_offset);
		t = t->next;
		i++;
	}
	printf("PCB %d: PC %d, Current page %d, Offset %d\n", i, t->pcb.PC, t->pcb.PC_page, t->pcb.PC_offset); // Print last node
}

void resetReadyQueue(){
	head = NULL;
	tail = NULL;
}

int checkPCBFiles(char * name){
	int a = -1;
	struct RQNode *t;
	t = head;

	if (t == NULL) {
		printf("Linked list is empty.\n");
		return a;
	}
	while (t->next != NULL) {
		a = strcmp(t->pcb.fileName, name);
		if(a == 0)
		    return a;
		t = t->next;

	}
	a = strcmp(t->pcb.fileName, name); // Print last node
	return a;
}

int myinit(char *filename) {
	int errcode = 0;

	char fInput[1000];
	fileNameExec = filename;
	FILE *f = fopen(filename, "r");
	int start = 0;
	int end = 0;
	//only read file if could open succesfully
	if(f != NULL){
	    int launch = launcher(f);
	    //launching adds to ram, creates PCb and adds it to ready queue
	    if(launch == 1){
		    printf("lauching successful\n");
		}
		else{
		    printf("Could not launch program, aborting\n");
		    errcode = -4;
		    //initiateRAM();
		    //resetReadyQueue();
		}
	}
	else{
		printf("File %s does not exist\n", filename);
		errcode = -4;
	}
	return errcode;
}

int scheduler(){
    int lockID = getLock();
	int errcode = 0;
	int quanta = 2;
	int i = 0;
	int enqueue = 1;
	struct RQNode *t;
	while(head != NULL){
		printf("inside scheduler loop\n");
		t = head;
		head = t->next;
		struct PCB p = t->pcb;
		setIP(p.PC, p.PC_offset);
		int q = quanta;
		int interr = runCPU(q);
		printf("Finished running, now at %d, error %d\n", p.PC+p.PC_offset, interr);
	    
	    //check if "quit" command was called, dont enqueue
		if(interr == -1){
		    enqueue = 0;
		    printf("quit command, done, lock id = %d\n", lockID);
		 }
		 //check wheter interrupt was triggered or not
		else if(interr == 1){
		    p.PC_page++;
		    if(p.PC_page > p.pages_max)//last page, dont enqueue
		        enqueue=0;
		    else{//not done, get next page and enqueue PCB
		        if(p.pageTable[p.PC_page-1] != NULL){
		            p.PC = p.pageTable[p.PC_page-1]*4;
		            p.PC_offset = 0;
		            enqueue=1;
		        }
		        //frame is not paged yet, so we need find it
		        else{
		            FILE * backFile = fopen(p.fileName, "r");
		            int frame = findFrame();
	                int victimFrame = -1;
	                printf("found frame: %d, victim: %d\n", frame, victimFrame);
	                if(frame==-1){
	                    victimFrame = findVictim(&p);
	                    loadPage(p.PC_page-1, backFile, victimFrame);
	                    p.pageTable[p.PC_page-1] = victimFrame;
	                }
	                else{
	                    loadPage(p.PC_page-1, backFile, frame);
	                    p.pageTable[p.PC_page-1] = frame;
	                }
	    
	                fclose(backFile);
	                p.PC = p.pageTable[p.PC_page-1]*4;
		            p.PC_offset = 0;
		            enqueue=1;
		                    
		        }
		       
		    }
		}
		//no interrupt, updatePC and offset, enqueue
		else{
		    p.PC_offset = p.PC_offset+q;
		    //p.PC = p.PC+q;
		    enqueue = 1;
		}

		//don't enqueue
		if(enqueue == 1){
			printf("adding to queue again\n");
			addToReady((&p));
		}
		else{
		    //delete file if a pcb in queue does not have the same file
		    int i = checkPCBFiles(p.fileName);
		    if(i != 0){
		        i = remove(p.fileName);
		        printf("Program terminated, deleting file %s\n", p.fileName);
		    }
		    printQueue();
		}

	}
    if(lockID == 1){
	    printf("%d, cleaning up\n", i);
	    initiateRAM();
	    head = NULL;
	    tail = NULL;
	    resetLock(); //resetting lock
	    //at the end, free stuff
	    
    }
    printf("sched done, errcode = %d\n", i);
	return errcode;
}

int updateVictimPageTable(int victimFrame){
	int err = 0;
	int i = 0;
	struct RQNode *t;
	t = head;

	if (t == NULL) {
		printf("Linked list is empty, no victim pcb\n");
		return err;
	}
	while (t->next != NULL) {
	    for(int i = 0; i < t->pcb.pages_max; i++){
        //if the frame exists in the pagetable, get next number and reset loop
            if(t->pcb.pageTable[i] == victimFrame){
                printf("found victim pcb\n");
                t->pcb.pageTable[i]=-1;
                return err;
            }
        }
        
		t = t->next;
		i++;
	}
	//last node
	for(int i = 0; i < t->pcb.pages_max; i++){
            if(t->pcb.pageTable[i] == victimFrame){
                printf("found victim pcb\n");
                t->pcb.pageTable[i]=-1;
                return err;
            }
    }
	return err;
}
