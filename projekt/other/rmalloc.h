#ifndef __imalloc
#define __imalloc

// Allokera 'bytes' antal tecken i minnet. 'threshhold' sätter ett
// tröskelvärde för att förhindra att allt för små block skapas
// (fragmentering)
void init(unsigned int bytes, unsigned int threshhold);

// Allokera 'bytes' antal tecken i minnet
void *rmalloc(int bytes);

// Manipulera referensräknaren
void retain(void *address);
void release(void *address);

// För illustration av användande av minnesutrymmet i
// testprogrammet, inte en del av rmalloc
void dumpmem();

#endif


