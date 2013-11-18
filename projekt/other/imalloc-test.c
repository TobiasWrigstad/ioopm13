#include <stdio.h>
#include "imalloc.h"

int main(void) {
  init(4);
  dumpmem();
  int *a = imalloc();
  *a = 7;
  dumpmem();
  int *b = imalloc();
  *b = 8;
  dumpmem();
  int *c = imalloc();
  *c = 9;
  dumpmem();
  printf("Releasing %d, status %d\n", *c, release(c));
  dumpmem();
  retain(b);
  printf("Releasing %d, status %d\n", *b, release(b));
  dumpmem();
  printf("Releasing %d, status %d\n", *a, release(a));
  dumpmem();
  int *d = imalloc();
  *d = 6;
  dumpmem();
  int *e = imalloc();
  *e = 5;
  dumpmem();
  int *f = imalloc();
  *f = 4;
  dumpmem();
  int *g = imalloc();
  printf(g ? "got something\n" : "got null\n");
  dumpmem();
  return 0;
}
