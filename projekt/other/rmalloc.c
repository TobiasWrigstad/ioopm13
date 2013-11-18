#include <stdlib.h>
#include <stdio.h>
#include "rmalloc.h"

/* Implementation of an extremely simple scheme for manual memory
 * management. It uses a unified block list with memory address
 * sorting. This allows merging adjacent blocks which decreases
 * fragmentation, but allocation and deallocation is slow.
 *
 * Each allocated memory block has a reference count which is
 * manipulated using retain and release calls.
 */

typedef struct _chunk chunk;
typedef chunk *Chunk;
struct _chunk {
  void* start;
  unsigned size;
  Chunk next;
  unsigned short free;
  unsigned short refcount;
};

static Chunk H;
static unsigned int Threshhold; 

void init(unsigned int bytes, unsigned int threshhold) {
  char *memory = (char*) malloc(bytes);
  H = (Chunk) malloc(sizeof(chunk));
  H->start = (void*) memory;
  H->size = bytes;
  H->next = NULL;
  H->free = 1;
  Threshhold = threshhold;
  while (--bytes) memory[bytes] = 0;
}

static short fits(Chunk c, int bytes) {
  return c && (c->size >= bytes && c->free);
}

static void *split(Chunk c, int bytes) {
  if (c->size > bytes + Threshhold) {
    c->next = malloc(sizeof(chunk));
    c->next->start = c->start + bytes;
    c->next->size  = c->size  - bytes;
    c->next->next  = NULL;
    c->next->free  = 1;
  }
  c->free = 0;
  c->size = bytes;
  c->refcount = 1;
  return (void*) c->start;
}

void *rmalloc(int bytes) {
  Chunk c = H;
  while (!fits(c, bytes)) c = c->next;
  if (c) {
    return split(c, bytes);
  } else {
    return NULL; 
  }
}

static void *__tfreeSimple(void* address) {
  Chunk c = H;
  while (c && c->start != address) {
    c = c->next;
  }
  if (c) {
    c->free = 1;
    return c->start;
  } else {
    return NULL; 
  }
}

static void combine(Chunk a, Chunk b) {
  a->size += b->size;
  a->next =  b->next;
  free(b);
}

static void *__tfreeDefrag(void* address) {
  Chunk c = H;
  Chunk p = NULL;
  while (c) {
    if (c->start == address) {
      for (int offset=0; offset < c->size; ++offset) *((char*) c->start+offset) = 0;
      c->free = 1;
      Chunk n = c->next;
      while (n && n->free) {
	combine(c, n);
	n = c->next;
      }
    }
    if (c->free) {
      if (p) {
	combine(p,c);
      } else {
	p = c;
      }
    } else {
      p = NULL;
    }
    c = c->next;
  }
  return c ? address : NULL;
}

static void *tfree(void* address) {
  return __tfreeDefrag(address);
}

void retain(void* address) {
  Chunk c = H;
  while (c && c->start != address) {
    c = c->next;
  }
  if (c) {
    c->refcount++;
  }
}

void release(void* address) {
  Chunk c = H;
  while (c && c->start != address) {
    c = c->next;
  }
  if (c && c->refcount-- == 1) {
    tfree(address);
  }
}

void dumpmem() {
  Chunk c = H;
  while (c) {
    printf("Start address: %ld, Size: %d, Free: %d (Refcount: %d)\n", (long) c->start, c->size, c->free, c->refcount);
    c = c->next;
  }
  puts("---------------------------------------------");
}

