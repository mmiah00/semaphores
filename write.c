#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <unistd.h>

#define KEY1 24601
#define KEY2 24602

int main () {
  printf ("trying to get in\n");
  struct sembuf buf;
  buf.sem_num = 0;
  buf.sem_op = -1;
  int sem = semget(KEY1, 1, 0644);
  if (sem < 0) {
    printf ("Error: %s\n", strerror (errno));
    return 0;
  }
  semop (sem, &buf, 1);
  int shm = shmget (KEY2, sizeof (int), IPC_CREAT | IPC_EXCL | 0644);
  if (shm < 0) {
    printf ("Shared Memory Error: %s\n", strerror (errno));
    return 0;
  }
  else {
    int fd = open ("new.txt", O_WRONLY | O_APPEND);
    char * last = shmat (shm, 0,0);
    char *next;
    printf ("Last addition: %s\n", last);
    printf ("Your addition: ");
    fgets (next, 1000, stdin);
    write (fd, next, strlen (next));
    printf ("%s\n", next);
    strcpy (last, next);
    shmdt (last);
    close (fd);

    buf.sem_op = 1;
    semop (sem, &buf, 1);
  }
  return 0;
}
