extern char *ram[1000];

char * getRAM(int k);
int addToRAM(FILE *p, int *start, int *end);
void cleanUpRAM();
void printRAM();
