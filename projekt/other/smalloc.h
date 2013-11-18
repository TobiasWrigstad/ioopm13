#ifndef __smalloc
#define __smalloc

// Allokera ett sammanhängande minnesutrymme om 'bytes' bytes för
// smalloc, nollställ det
void init(unsigned int bytes);

// Allokera 'bytes' antal tecken i minnet
void *smalloc(int bytes);

// Frigör blocket som startar med adressen 'address'
void *sfree(void* address);

// För illustration av användande av minnesutrymmet i
// testprogrammet, inte en del av smalloc
void dumpmem();

#endif
