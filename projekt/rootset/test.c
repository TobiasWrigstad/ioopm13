
#include "rootset.h"
#include "smalloc.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

AddressSpace mkAddressSpace(RawPtr start, RawPtr end, Allocator alloc) {
  assert(start < end);
  AddressSpace result = (alloc ? alloc : malloc)(sizeof(addressspace));
  result->start = start;
  result->end   = end;
  return result;
}

void print(void *ptr, void *ignore) {
  printf("Adding to rootset: %p from variable %p\n", *((void**) ptr), ptr);
}

void f(void *h) {
  return;
}

void someFunction(int recurse) {
  int i;
  char c = i + c;
  void *temp2 = NULL;
  if (recurse) {
    void *temp;
    temp = smalloc(1);
    printf("Creating new object on %p, storing it in stack var %p\n", temp, &temp);
    temp2 = temp;
    f(temp2);
    someFunction(--recurse);
  } else {
    traverseStack(mkAddressSpace(H->start, ((char*)H->start) + (1024*1024), NULL), print, NULL);
  }
}

int main(void) {
  // This must be in main!
  SET_STACK_BOTTOM

  init(1024*1024);

  
  printf("malloc(1):    [%p..%p]\n", H->start, H->start+H->size);
  printf("Heap size      %d Mb\n", (H->size)/1024/1024);

  someFunction(5);
  return 0;
}

