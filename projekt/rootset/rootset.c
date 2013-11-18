
/*
  Solaris info
  From: http://www.ribeiros.co.uk/documents/solaris_memoryarch.pdf
  Page 176
  On a 32 bit SPARC: 
  Stack starts: 0xFFBEC000
  Stack ends:   0xFF3DC000
  On a 64 bit SPARC: 
  Stack starts: 0xFFFFFFFF.7FFFC000
  Stack ends:   0xFFFFFFFF.7F7F0000
  On a X86:
  Stack starts: 0x8048000
  Stack ends:   0x0 (grows downward)
 */


#include "rootset.h"
#include <setjmp.h>
#include <stdint.h>

void *__g_stack_bottom__;

#ifdef __sparc__
#   if defined(__arch64__)
#     define ALIGNMENT 8
#   else
#     define ALIGNMENT 4
#   endif
#endif

int inAddressSpace(void *ptr, AddressSpace s) {
  return s->start <= (char *)ptr && (char *)ptr <= s->end;
}

void traverseStack(AddressSpace s, MarkFun mark, void *data) {
  /* 
     Looks at all sizeof(void*) chunks of bytes from stack_bottom
     to stack_top and if they contain a bit-pattern that, when
     treated as a pointer, looks into the address space denoted
     by s, call mark and pass along the extra argument data. 
  */

  void *stack_top;
  CURRENT_SP(stack_top);
#ifdef DEBUG
  printf("Scanning addresses %p to %p (%d)\n", min(stack_top, stack_bottom), 
	                                       max(stack_top, stack_bottom), 
	                                       max(stack_top, stack_bottom)-min(stack_top, stack_bottom));
#endif

  jmp_buf buf;
  void *end = (void *) &buf+sizeof(jmp_buf);
  setjmp(buf);
  for (void *cursor = (void *) &buf;
       end-cursor >= sizeof(void*);
       ++cursor) {
#ifdef __sparc__
    if (((uintptr_t) cursor) % ALIGNMENT != 0)
      continue;
#endif
#ifdef DEBUG
    printf("Found pointer to %p\n", *(void**)cursor);
#endif
    if (inAddressSpace(*(void**)cursor, s)) {
      mark(cursor, data);
    }
  }

  for (void *cursor = stack_top;
       __g_stack_bottom__-cursor >= sizeof(void*); 
       ++cursor) {
#ifdef __sparc__
    if (((uintptr_t) cursor) % ALIGNMENT != 0)
      continue;
#endif
#ifdef DEBUG
    printf("Found pointer to %p\n", *(void**)cursor);
#endif
    if (inAddressSpace(*(void**)cursor, s)) {
      mark(cursor, data);
    }
  }
}
