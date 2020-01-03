#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

#define KEY1 24601
#define KEY2 24602

int main () {
  printf ("trying to get in\n");
  int sem = semget(KEY, 1, 0);
  struct sembuf buf;
  if (sem < 0) {
    printf ("Error: %s\n", strerror (errno));
  }
  else {
    semop (sem, &sb, 1);
    int shm = shmget (KEY2, 100, 0);
    if (shm < 0) {
      printf ("Error: %s", strerror (errno));
    }
    else {
      int fd = open ("file.txt", O_WRONLY);
      printf ("Last addition: %s\n", shmat (shm, 0,0));
      char *next; ;
      fgets (next, 256, stdin);
      write (fd, next, strlen (next));
      printf ("Your addition: %s", next);
      close (fd); 
    }
  }
  return 0;
}
