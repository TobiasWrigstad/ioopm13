#include <stdio.h>
#include "smalloc.h"


int main(void) {
  init(1024);
  dumpmem();
  void *a = smalloc(sizeof(int));
  dumpmem();
  void *b = smalloc(3);
  dumpmem();
  void *c = smalloc(3);
  dumpmem();
  sfree(c);
  dumpmem();
  sfree(b);
  dumpmem();
  sfree(a);
  dumpmem();
  unsigned int *d = (unsigned int*) a; 
  printf("%u\n", *d);
}
