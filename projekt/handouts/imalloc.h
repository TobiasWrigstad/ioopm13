#ifndef __imalloc_h
#define __imalloc_h

/*
 * imalloc.h
 *
 * This file contains the public specifications for using the
 * imalloc allocator used as a course project for the 2013 IOOP/M
 * course.
 *
 * Note that this specification might evolve as the project is
 * running, f.ex. due to technical as well as educational bugs and
 * insights.
 *
 * You may NOT alter the definitions in this file.
 *
 */

#define chunk_size unsigned int
#define Kb *1024
#define Mb Kb Kb

/* Enumeration constants used by to define how the freelist should
 * be sorted.
 */
enum { ASCENDING_SIZE = 1, DESCENDING_SIZE = 2, ADDRESS = 4 } FreelistStyle;

/* Enumeration constants used by to specify kind of memory
 * manager.
 */
enum { MANUAL = 8, REFCOUNT = 16, GCD = 32 } MallocStyle;

/* Not mandatory. If you want to support copying GC, you are free
 * to think about how to achieve that! 
 */
enum { NON_COPYING = 64, COPYING = 128 } GCStyle;

/* The client's pointer to a memory manager. This must be passed
 * as argument to most functions of imalloc.
 */
typedef struct style *Memory;

/* Types used for function pointers in the memory manager struct.
 */
typedef void *(*RawAllocator)(Memory mem, chunk_size size);
typedef void *(*TypedAllocator)(Memory mem, char* typeDesc);
typedef unsigned int(*Manipulator)(Memory mem, void *ptr);
typedef unsigned int(*Global)(Memory mem);
typedef unsigned int(*Local)(void *ptr);

/* Functions for automatic garbage collecting memory manager
 * (mark-sweep)
 */
typedef struct {
  TypedAllocator alloc;
  Global         collect;
} GC;

/* Functions for reference counting memory manager */
typedef struct {
  Local       retain;
  Manipulator release;
  Local       count;
} Refcount;

/* Functions for the manual memory manager */
typedef struct {
  RawAllocator alloc;
  Global       avail;
  Manipulator  free; 
} manual, *Manual; 

/* Functions for the manual memory manager */
typedef struct {
  RawAllocator alloc;
  Refcount     rc; 
  GC           gc; 
} managed, *Managed;

/* Return type specification for iMalloc */
typedef union {
  manual  manual;
  managed managed;
} style;


//////////////////// Public Functions ////////////////////

/* Initiates the malloc library to be used. memsiz defines the
 * maximum amount of memory that can be used. flags specifies kind
 * of memory manager and allows fine-tunes some options.
 */ 
struct style *iMalloc(chunk_size memsiz, unsigned int flags);

#endif
