#include <stdio.h>
#include "rmalloc.h"

int main(void) {
  init(12, 1);
  dumpmem();
  void *a = rmalloc(4);
  dumpmem();
  void *b = rmalloc(3);
  dumpmem();
  void *c = rmalloc(3);
  dumpmem();
  release(c);
  dumpmem();
  retain(b);
  release(b);
  dumpmem();
  release(a);
  dumpmem();
}
