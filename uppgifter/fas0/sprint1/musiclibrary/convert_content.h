#ifndef ID3PRINT_H
#define ID3PRINT_H

#include <stdlib.h>

/**
 * This function receives a pointer to the beginning of the content of
 * an ID3 frame and its size and converts it into a UTF-8 encoded
 * string. You can pass this the output of this function to printf.
 *
 * The output pointer points to freshly allocated memory and has to be
 * freed by the user.
 */
char *convert_content(char *content, size_t len);

#endif
