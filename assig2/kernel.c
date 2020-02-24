/* Shell written by Sabina Sasu, 260803977*/
/* ECSE427 Mcgill Winter 2020 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "ram.h"
#include "pcb.h"
#include "cpu.h"


struct RQNode{
	struct PCB pcb;
	struct RQNode *next;
};
struct RQNode *head, *tail;

int main(){

	printf("Kernel 1.0 loaded!\n");
	shellUI();
}

// add the PCB to the tail of the Ready Queue
void addToReady(struct PCB *new_pcb){
	int PC=new_pcb->PC;
	int start = new_pcb->start;
	int end = new_pcb->end;
	struct PCB new_p = {PC, start, end};
	struct RQNode *new;
	//printf("pcb created, %d, %d, %d\n", new_p.PC, new_p.start, new_p.end);
	new = (struct RQNode*)malloc(sizeof(struct RQNode));
	new->pcb = new_p;
	new->next=NULL;
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
	int i = 0;
	struct RQNode *t;

	t = head;

	if (t == NULL) {
		printf("Linked list is empty.\n");
		return;
	}
	printf("printint queue\n");
	while (t->next != NULL) {
		printf("%d, %d, %d\n", i, t->pcb.start, t->pcb.end);
		t = t->next;
		i++;
	}
	printf("%d, %d, %d\n", i, t->pcb.start, t->pcb.end); // Print last node
}

void resetReadyQueue(){
	head = NULL;
	tail = NULL;
}

int myinit(char *filename) {
	int errcode = 0;

	char fInput[1000];
	FILE *f = fopen(filename, "r");
	int start = 0;
	int end = 0;
	//only read file if could open succesfully
	if(f != NULL){
		errcode = addToRAM(f, &start, &end);

		if(errcode != 4){
			//printf("added to ram, %d, %d\n", start, end);
			struct PCB * p= makePCB(start, end);
			//printf("pcb created3 %d, %d\n", p->PC, p->end);
			addToReady(p);
			//printf("added to queue\n");
		}
	}
	else{
		printf("File %s does not exist\n", filename);
		errcode = 4;
		cleanUpRAM();
		resetReadyQueue();
	}
	return errcode;
}


int scheduler(){
	int errcode = 0;
	int quanta = 2;
	int i = 0;
	struct RQNode *t;
	while(head != NULL){
		//printf("inside scheduler\n");
		t = head;
		head = t->next;
		struct PCB p = t->pcb;
		setIP(p.PC);
		int q = quanta;
		if(quanta > (p.end-p.PC)){
			q = p.end-p.PC;
		}
		runCPU(q);
		//printf("finished running, now at %d\n", p.PC+q);
		//update PC
		p.PC = p.PC+q;

		//don't enqueue
		if(!(p.PC >= p.end)){
			//printf("adding to queue again\n");
			addToReady((&p));
		}

	}

	//printf("%d, cleaning up\n", i);
	cleanUpRAM();
	head = NULL;
	tail = NULL;
	//at the end, free stuff

	return errcode;
}
