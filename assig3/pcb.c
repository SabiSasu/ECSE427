/*
 * kernel.c
 *
 *  Created on: Feb 12, 2020
 *      Author: Bubble
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcb.h"

//create a PCB instance using malloc
struct PCB* makePCB(int start, int end){
	struct PCB new = {start, start, end};
	struct PCB *p2 = &new;
	//printf("pcb created3 %d, %d\n", p2->PC, p2->end);
	return p2;
}
