/*
 * kernel.c
 *
 *  Created on: Feb 12, 2020
 *      Author: Bubble
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ram.h"
#include "shell.h"

struct CPU {
	int IP; //instruction pointer
	char IR[1000]; //like PC, points to instruction in ram
	int quanta; //quanta value
	int offset;
} CPU;

void setIP(int a, int offset){
	CPU.IP = a;
	CPU.offset = offset;
}

int runCPU(int quanta){
	int errcode = 0;
	CPU.quanta = quanta;
	while(CPU.quanta > 0){
		//retreive ram line
		strcpy(getRAM(CPU.IP+CPU.offset), CPU.IR);
		
		//check if line in ram exists before running it
		//printf("Q: %d, %s, %s\n", CPU.quanta, getRAM(CPU.IP), CPU.IR);
		if(getRAM(CPU.IP+CPU.offset) != NULL){
		    printf("\n%s\n", getRAM(CPU.IP + CPU.offset));
		    errcode = parse(getRAM(CPU.IP + CPU.offset));
		    
		    if(errcode == -1)
		        return errcode;
		    CPU.offset = CPU.offset+1;
		    printf("done parsing, errcode: %d, offset: %d\n", errcode, CPU.offset);
		}
		else//if rest of frame is empty, trigger interrupt
		    return 1;
		
		//done with frame, pseudo-interrupt to page fault
		if(CPU.offset>=4){
		    printf("CPU offset at 4\n");
		    return 1;
		}
		CPU.quanta--;
	}
	return errcode;
}
