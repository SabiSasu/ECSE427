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
} CPU; //= (sizeof(struct CPU))*malloc(sizeof(struct CPU));

void setIP(int a){
	CPU.IP = a;
}

void runCPU(int quanta){
	int errcode = 0;
	CPU.quanta = quanta;
	while(CPU.quanta > 0){
		//retreive ram line
		strcpy(getRAM(CPU.IP), CPU.IR);
		//run the line
		//printf("Q: %d, %s, %s\n", CPU.quanta, getRAM(CPU.IP), CPU.IR);
		errcode = parse(getRAM(CPU.IP));
		CPU.IP++;
		CPU.quanta--;
	}
}
