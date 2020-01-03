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

union semun {
  int              val;
  struct semid_ds *buf;
  unsigned short  *array;
  struct seminfo  *__buf;
};

int sem;
union semun semvals;

void c () { //creating
  printf ("Creating...\n");
  sem = semget(KEY1, 1, IPC_CREAT | 0644);
  if (sem > -1) {
    printf ("\tSemaphore created!\n");
    semvals.val = 1;
    semctl (sem, 0, SETVAL, semvals.val);
    printf ("\tShared memory created!\n");
    int fd = open ("new.txt", O_CREAT, 0644);
    printf ("\tFile created!\n");
    if (fd == -1) {
      printf ("didn't open\nError: %s\n", strerror (errno));
    }
    close (fd);
  }
}

void v () { //viewing
  printf ("The story so far: \n");
  int fd = open ("new.txt", O_RDONLY);
  if (fd == -1) {
    printf ("didn't open\nError: %s\n", strerror (errno));
  }
  else {
    char * line;
    line[0] = '\0';
    read (fd, line, 10000);
    if (strlen (line) > 0) {
      *(srrchr (line, '\n') + 1) = '\0'; 
    }
    printf ("Story so far: %s\n", line);
    close (fd);
  }

}

void r () { //removing
  sem = semget(KEY1, 1, 0);
  if (sem < 0) {
    printf ("couldn't remove\nError: %s\n", strerror (errno));
  }
  else {
    printf ("Trying to get in...\n");
    semctl(shmget (KEY2, 100, 0), IPC_RMID, 0);
    printf ("Shared memory removed.\n");
    remove ("new.txt");
    printf ("File removed.\n");
    semctl(sem, IPC_RMID, 0);
    printf ("Semaphore removed.\n");
  }
}

int main(int argc, char * argv[]) {
  if (argc == 2) {
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
