#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>

int main(){
  int semid = semget(ftok("control.c",30),1,IPC_CREAT);
  
  struct sembuf buf; 
  buf.sem_op = -1;
  buf.sem_num = 0;
  buf.sem_flg = SEM_UNDO;
  
  semop(semid,&buf,1);
  
  
  int memid = shmget(ftok("control.c",43), 128, IPC_CREAT);
  char *a;
  a = shmat( memid, 0, 0 );
  
  if (a){
    printf("Previous line: %s\n", a);
    printf("Please input next line: ");
  }

  else{
    printf("Input the first line:");
  }
  
  fgets(a,sizeof(a),stdin);

  int fd = open("./telephone.txt", O_APPEND);
  write(fd,a,sizeof(a));
  close(fd); 
  
  return 0;
}
