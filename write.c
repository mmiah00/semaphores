#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <unistd.h>

#define KEY1 24601
#define KEY2 24602

int main () {
  printf ("trying to get in\n");
  int sem = semget(KEY1, 1, 0);
  struct sembuf buf;
  buf.sem_num = 0;
  buf.sem_op = -1;
  if (sem < 0) {
    printf ("Error: %s\n", strerror (errno));
  }
  else {
    semop (sem, &buf, 1);
    int shm = shmget (KEY2, 100, 0);
    if (shm < 0) {
      printf ("Error: %s", strerror (errno));
    }
    else {
      int fd = open ("file.txt", O_WRONLY);
      char * last = shmat (shm, 0,0); 
      printf ("Last addition: %s\n", last);
      char *next; ;
      fgets (next, 256, stdin);
      write (fd, next, strlen (next));
      printf ("Your addition: %s", next);
      close (fd);
      shmdt (next);
      buf.sem_op = 1;
      semop (sem, &buf, 1);
    }
  }
  return 0;
}
