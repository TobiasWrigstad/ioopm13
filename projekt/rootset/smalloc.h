#ifndef __smalloc
#define __smalloc

// Allokera ett sammanh�ngande minnesutrymme om 'bytes' bytes f�r
// smalloc, nollst�ll det
void init(unsigned int bytes);

// Allokera 'bytes' antal tecken i minnet
void *smalloc(int bytes);

// Frig�r blocket som startar med adressen 'address'
void *sfree(void* address);

// F�r illustration av anv�ndande av minnesutrymmet i
// testprogrammet, inte en del av smalloc
void dumpmem();

typedef short bool;

typedef struct _chunk chunk;
typedef chunk *Chunk;
struct _chunk {
  void* start;
  unsigned size;
  Chunk next;
  bool free;
};

Chunk H;

#endif
