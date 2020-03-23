struct PCB {
	int PC;
	int start;
	int end;
 	int pageTable[10];
	int PC_page;
	int PC_offset;
	int pages_max;
};

struct PCB* makePCB(int start, int end);

