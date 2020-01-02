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


int main(int argc, char * argv[]) {
  if (argc == 2) {
    int semd;
    int v, r;
    char input[3];

    semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (semd == -1) {
      printf("error %d: %s\n", errno, strerror(errno));
      semd = semget(KEY, 1, 0);
      v = semctl(semd, 0, GETVAL, 0);
      printf("semctl returned: %d\n", v);
    }
    else {
      union semun us;
      us.val = 1;
      r = semctl(semd, 0, SETVAL, us);
      printf("semctl returned: %d\n", r);
    }
    char * flag;
    fgets (flag, 5, stdin);
    if (strcmp (flag, "-r")) {
      semctl (semd, IPC_RMID, 0);
      /*
      printf("Would you like to remove the semaphore?(y/n) ");
      fgets(input, 3, stdin);

      if (input[0] == 'y') {
        semctl(semd, IPC_RMID, 0);
        printf("segment deleted\n");
      }*/
    }


    return 0;
  }
  else {
    printf ("Please add a flag (-c, -v, -r) \n");
  }
}
