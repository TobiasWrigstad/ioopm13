
#ifndef __IOOPM_ROOTSET_H__
#define __IOOPM_ROOTSET_H__

#include <stddef.h>

/* 
   NOTE: rpb (and ebp, fp) all point to the start of the current
   frame, and not to the top of the stack, i.e., it's where the
   frame starts and not where it would be safe to push a new
   frame. If you're really looking for the top of the stack it's
   rsp, esp and fp, on the respective platforms. The resoning is
   that traverseStack does not itself hold any pointers to objects
   in the user area, so looking at the top frame is useless.
*/

// This macro stores the address of the current stack frame in
// "var". Note the "var" MUST be an lval!
#ifdef __x86_64__
#   define CURRENT_SP(var) __asm__("mov %%rbp, %0":"=r"(var))
#endif
#ifdef __i386__
#   define CURRENT_SP(var) __asm__("mov %%ebp, %0":"=r"(var))
#endif
#ifdef __sparc__
#   if defined(__arch64__)
// NOTE: The base pointer in Sparc64 is 2047 off.
#     define CURRENT_SP(var) __asm__("mov %%fp, %0":"=r"(var)); ((var) += 2047);
#   else
#     define CURRENT_SP(var) __asm__("mov %%fp, %0":"=r"(var))
#   endif
#endif

extern void *__g_stack_bottom__;


/* **************************************************************** */
/* ******************** START PUBLIC INTERFACE ******************** */
/* **************************************************************** */

/*
  NOTE: It is imperative that this macro is present in the main
  function!
 */
#define SET_STACK_BOTTOM CURRENT_SP(__g_stack_bottom__);


typedef void (*MarkFun)(void *ptr, void *data);
typedef void*(*Allocator)(size_t size);

typedef char * RawPtr;

typedef struct {
  RawPtr start;
  RawPtr end;
} addressspace, *AddressSpace;


/*
  This function will traverse the stack and registers, looking for
  bit-patterns of size sizeof(void *). If such a bit-pattern, when
  interpreted as a pointer, is an address into the supplied
  address space, the mark function is called with the found
  pointer and the auxiliary data argument.

  Arguments:
  - s: must be a valid address space
  - mark: must not be NULL
  - data: may be NULL
 */
void traverseStack(AddressSpace s, MarkFun mark, void *data);


#endif
