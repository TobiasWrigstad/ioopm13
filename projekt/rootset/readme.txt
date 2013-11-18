Usage: 

include rootset.h. Call SET_STACK_BOTTOM on the first line in
main. Then use traverseStack to traverse the stack. Look at 
the example in test.c for guidance. 

Smalloc is used in the test, but has nothing to do with the
definition of traverseStack. 

This is guaranteed to work on the Solaris machines at the
department, and can be used elsewhere with varying degree of
success. YMMV. 

