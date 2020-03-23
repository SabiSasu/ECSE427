extern char *ram[1000];

char * getRAM(int k);
void initiateRAM();
void loadPageRAM(int frame, char *fInput);
int addToRAM(FILE *p, int *start, int *end);
void cleanUpRAM();
void printRAM();
void printAllRAM();
int getNextFrame();
void clearFrame(int frame);
