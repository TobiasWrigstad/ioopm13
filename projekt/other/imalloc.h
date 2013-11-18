#ifndef __imalloc
#define __imalloc

// Allokera ett sammanhängande minnesutrymme om 'bytes' bytes för
// smalloc, nollställ det
void init(unsigned int bytes);

// Allokera sizeof(int) antal tecken i minnet
int *imalloc();

// Manipulera referensräknaren
int retain(int *address);
int release(int *address);

// För illustration av användande av minnesutrymmet i
// testprogrammet, inte en del av imalloc
void dumpmem();

#endif


