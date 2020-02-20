/*
 * kernel.c
 *
 *  Created on: Feb 12, 2020
 *      Author: Bubble
 */
struct CPU {
	int IP; //instruction pointer
	char IR[1000]; //like PC, points to instruction in ram
	int quanta; //quanta value
};



