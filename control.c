#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

#define KEY 24602

union semun {
  int              val;
  struct semid_ds *buf;
  unsigned short  *array;
  struct seminfo  *__buf;
};

void c () { //creating
  union semun semvals;
  printf ("Creating...\n");
  int sem = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if (sem > -1) {
    printf ("\tSemaphore created!\n");
    semvals.val = 1;
    semctl (sem, 0, SETVAL, semvals.val);
    printf ("\tShared memory created!\n");
    int fd = open ("file.txt", O_CREAT, 0644);
    printf ("\tFile created!\n");
    if (fd == -1) {
      printf ("didn't open");
    }
    close (fd);
  }
}

void v () { //viewing
  printf ("The story so far: \n");
  int fd = open ("file.txt", O_RDONLY);
  if (fd == -1) {
    printf ("didn't open");
  }

}

void r () { //removing
  int sem = semget(KEY, 1, 0);
}

int main(int argc, char * argv[]) {
  if (argc == 2) {
    int semd;
    int r;

    semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (semd == -1) {
      printf("error %d: %s\n", errno, strerror(errno));
    }
    else {
      union semun us;
      us.val = 1;
      r = semctl(semd, 0, SETVAL, us);
    }
    char * flag = argv[1];
    if (strcmp (flag, "-c") == 0) {
      c (); //creating
    }
    else {
      if (strcmp (flag, "-v") == 0) {
        v (); //viewing
      }
      else {
        r (); //removing
      }
    }
    /*
    if (strcmp (flag, "-r")) {
      semctl (semd, IPC_RMID, 0);

      //print story
      printf ("shared memory removed\nfile removed\nsemaphore removed");
    }*/

  }
  else {
    printf ("Please add a flag (-c, -v, -r) \n");
  }
  return 0;
}
