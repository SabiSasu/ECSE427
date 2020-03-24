int launcher(FILE *p);
int findFrame();
int findVictim(struct PCB *p);
void loadPage(int pageNumber, FILE *f, int frameNumber);
int updatePageTable(struct PCB *p, int pageNumber, int frameNumber, int victimFrame);
