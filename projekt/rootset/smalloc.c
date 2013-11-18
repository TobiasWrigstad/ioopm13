#include <stdlib.h>
#include <stdio.h>
#include "smalloc.h"

// Allokera ett sammanhängande minnesutrymme för smalloc, nollställ det
void init(unsigned int bytes) {
  char *memory = (char*) malloc(bytes);
  H = (Chunk) malloc(sizeof(chunk));
  H->start = (void*) memory;
  H->size = bytes;
  H->next = NULL;
  H->free = 1;
  while (--bytes) memory[bytes] = 0;
}

static bool fits(Chunk c, int bytes) {
  return c && (c->size >= bytes && c->free);
}

static void *split(Chunk c, int bytes) {
  if (c->size > bytes) {
    c->next = malloc(sizeof(chunk));
    c->next->start = c->start + bytes;
    c->next->size  = c->size  - bytes;
    c->next->next  = NULL;
    c->next->free  = 1;
  }
  c->free = 0;
  c->size = bytes;
  return (void*) c->start;
}

void *smalloc(int bytes) {
  Chunk c = H;
  while (!fits(c, bytes)) c = c->next;
  if (c) {
    return split(c, bytes);
  } else {
    return NULL; 
  }
}

static void *__sfreeSimple(void* address) {
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

static void *__sfreeDefrag(void* address) {
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

void *sfree(void* address) {
  // return __sfreeSimple(address); // Enklare variant som inte defragmenterar
  return __sfreeDefrag(address);
}

void dumpmem() {
  Chunk c = H;
  while (c) {
    printf("Start address: %ld, Size: %d, Free: %d\n", (long) c->start, c->size, c->free);
    c = c->next;
  }
  puts("---------------------------------------------");
}
