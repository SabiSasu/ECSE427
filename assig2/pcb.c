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
	printf("pcb created1\n");
	struct PCB new = {start, start, end};
	printf("pcb created2\n");
	struct PCB *p2 = &new;
	printf("pcb created3\n");
	return p2;
}
