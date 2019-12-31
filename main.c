#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

void create () {
}

void remove () {
}

void view () {
  printf ("The story so far: \n");
}

int main (int argc, char * argv[]) {
  int s;
  if (argc == 2) {
    char * flag = argv[1];
    if (strcmp (flag, "-c")) {
      create ();
    }
    if (strcmp (flag, "-r")) {
      remove ();
    }
    if (strcmp (flag, "-v")) {
      view ();
    }
  }
  return 0;
}
