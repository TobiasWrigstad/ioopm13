#include <stdlib.h>
#include <stdio.h>
#include "imalloc.h"

typedef struct _intcell {
  int value;
  unsigned short refcount; 
} intcell, *Intcell;

typedef struct _chunk chunk;
typedef chunk *Chunk;
struct _chunk {
  unsigned int size;
  Chunk next;
  Intcell start;
  Intcell nextFree;
};

static Chunk H; 

void init(unsigned int size) {
  H  = (Chunk) malloc(sizeof(struct _chunk));
  H->size  = size;
  H->next  = NULL;
  H->start = H->nextFree = (Intcell) calloc(sizeof(intcell), size);
}

static Intcell findNextFree(Chunk h) {
  Intcell c = h->start;
  int offset = 0;
  while (offset < h->size && c[offset].refcount) ++offset;

  if (offset == h->size) { // Out of memory
    return h->nextFree = NULL;
  }

  return h->nextFree = c+offset;
}

int *imalloc() {
  if (H->nextFree == NULL) {
    // Out of memory!
    return NULL;
  } else {
    Intcell c = H->nextFree;
    c->refcount = 1;
    findNextFree(H);
    return &(c->value);
  }
}

static inline Intcell cellForAddress(int* address) {
  Intcell c = (Intcell) address;
  int index = (c - H->start) / sizeof(intcell);
  return (0 <= index && index <= H->size) ? c : NULL;
}

int release(int *address) {
  Intcell c = cellForAddress(address);
  if (c) {
    c->refcount -= 1;
    return 1;
  }
  return 0;
}

int retain(int *address) {
  Intcell c = cellForAddress(address);
  if (c) {
    c->refcount += 1;
    return 1;
  }
  return 0;
}

void dumpmem() {
  for(int i=0; i<H->size; ++i) {
    if (H->start[i].refcount) 
      printf("[%d (%d)]", H->start[i].value, H->start[i].refcount);
    else
      printf("[  %d  ]", H->start[i].value);
  }
  printf("\n");
}

