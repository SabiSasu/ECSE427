/* Shell written by Sabina Sasu, 260803977*/
/* ECSE427 Mcgill Winter 2020 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "ram.h"
#include "pcb.h"


struct RQNode{
	struct PCB pcb;
	struct RQNode *next;
};
struct RQNode *head, *tail;

int main(){

	printf("Kernel 1.0 loaded!\n");

	/*

	head.next -> tail;
	tail.next -> head;
	 */

	shellUI();
}

// add the PCB to the tail of the Ready Queue
void addToReady(struct PCB *new_pcb){
	struct PCB new_p = *new_pcb;
	struct RQNode *new;
	printf("pcb created, %d\n", new_p.end);
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
			printf("added to ram, %d, %d\n", start, end);
			addToReady(makePCB(start, end));
			printf("added to queue\n");
		}
	}
	else{
		printf("File %s does not exist\n", filename);
		errcode = 4;
	}
	return errcode;
}


int scheduler(){
	int errcode = 0;

	int i = 0;
	struct RQNode *t;
	t = head;
	while (t->next != NULL) {
		t = t->next;
		i++;
	}
	i++;

	printf("%d, cleaning up\n", i);
	cleanUpRAM();
	head = NULL;
	tail = NULL;
	//at the end, free stuff

	return errcode;
}
