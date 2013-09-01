#include "convert_content.h"
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include<iconv.h>

//for info, look here: http://id3lib.sourceforge.net/id3/id3v2.3.0.html
char *convert_content(char *content, size_t size) {
  char *encoding;
  switch (*content) {
  case 0x00:
    encoding = "ISO-8859-1";
    break;
  case 0x01:
    encoding = "UCS-2";
    break;
  default:
    printf("Couldn't convert -- first byte is neither 0x00 nor 0x01 (is: %i)!\n", *content);
    return NULL;
  }

  //first byte consumed and interpreted, move on:
  size--;
  content++;

  iconv_t cd = iconv_open("UTF-8", encoding);
  if ((int)cd != -1) {
    size_t outsize = 2*size;
    char* outbuf = calloc(outsize,sizeof(char));
    if (!outbuf) {
      fprintf(stderr, "Could not allocate outbuf (outsize=%zi)!\n", outsize);
      return NULL;
    }
    char* outbuf_start = outbuf;
    if (iconv(cd, &content, &size, &outbuf, &outsize) != -1) {
      return outbuf_start;
    } else {
      printf("conversion failed: %s\n", strerror(errno));
      iconv_close(cd);
      free(outbuf_start);
      return NULL;
    }
  } else {
    printf("couldn't create conversion descriptor: %s\n", strerror(errno));
  }
  iconv_close(cd);
  return NULL;
}
