#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

int main (int argc, char * argv []) {
  printf ("trying to get in\n");
  int i = 1;
  while (true) {
    char * prevline;
    if (i = 1) {
      printf ("Last line: \n");
    }
    else {
      fgets (prevline, 100, argv[i - 1]);
      printf ("Last line: %s\n", prevline); 
    }
    char * new;
    fgets (new, 100, stdin);
    printf ("Your addition: %s\n", new);
  }
  return 0;
}
