#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include "ahead.h"
#include <errno.h>
#include <string.h>

union semun{
  int val; //value for SETVAL
  struct semid_ds *buf; //Buffer for IPC_STAT, IPC_SET
  unsigned short *array; //Array for GETALL, SETALL
  struct seminfo *__buf; //Buffer for IPC_INFO (Linux)
  };

int main(int argc, char* argv[]){
  int sd;
  char *a;
  int memid;
  int semid;
  
  if (argc != 2){
    if (argc > 2){
      printf("Too many arguments (1 expected)\n");
    }
    else {
      printf("Too few arguments (1 expected)\n");
    }
  }

  else if(!strncmp(argv[1],"-c",sizeof(argv[1]))){
    memid = shmget(ftok("control.c",43), 128, IPC_CREAT | IPC_EXCL | 0644);
    semid = semget(ftok("control.c",30), 1, IPC_CREAT | IPC_EXCL | 0644);
    union semun su;
    su.val = 1;
    int ctl = semctl(semid, 0, SETVAL, su);
    
    if (memid == -1 || semid == -1 || ctl == -1){
      printf("Error: %s\n", strerror(errno)); 
    }
    
    else{
      printf("Memory and semaphore created\n");
    }
  }

  else if(!strncmp(argv[1],"-r",sizeof(argv[1]))){
    struct shmid_ds d;
    memid = shmget(ftok("control.c",43), 128, IPC_CREAT);
    semid = semget(ftok("control.c",30), 1, IPC_CREAT);
    int memr = shmctl(memid, IPC_RMID, &d);
    int semr = semctl(semid, 0, IPC_RMID);

    if (memr == -1 || semr == -1){
      printf("Error: %s\n", strerror(errno));
    }

    else{
      printf("Memory and semaphore removed\n");
    }    
  }

  else{
    printf("Argument not recognized: %s\n",argv[1]);
  }
}
