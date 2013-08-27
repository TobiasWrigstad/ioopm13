#include <stdio.h> // för printf

// ökar parametern a med ett som sido-effekt
int plusEtt(int a) { 
  a = a + 1;
  return 0;
}

int main() {
  int a = 0;
  for( int i = 0; i < 3; i++) {
	  plusEtt(a);
	  printf("%d + 1 = %d\n",0,a);
  }
  return 0;
}
