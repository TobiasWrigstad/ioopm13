#ifndef __priv_malloc_h
#define __priv_malloc_h

/*
 * priv_imalloc.h
 *
 * This file contains private specifications for using the imalloc
 * allocator used as a course project for the 2013 IOOP/M course.
 *
 * Note that this specification might evolve as the project is
 * running, f.ex. due to technical as well as educational bugs and
 * insights.
 *
 * You MAY ADD and ALTER the definitions in this file.
 *
 */


/* Actual return type specifications for iMalloc */
struct private_manual {
  void  *data; 
  manual functions;
};

struct private_managed {
  void   *data; 
  managed functions;
};

#endif
