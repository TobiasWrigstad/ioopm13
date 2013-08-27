#include <stdio.h>

int main()
{
  char *names[] = {"Tobias Wrigstad", "Elias Castegren", "Tobias Skoglund"};
  int   rooms[] = {1338, 1357, 1419};
  int length = 3;
  for (int i = 0; i < length; ++i){
    printf("%s sitter i %d\n", names[i], rooms[i]);
  }
  return 0;
}