#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/shm.h>
#define key 0x1244
int main(int argc, char **argv)
{
    void *shared_mem;
    int *x;
    int shmid;
    shmid=shmget(key,2*(sizeof(int)),0666|IPC_CREAT);
    shared_mem=shmat(shmid,NULL,0);
    printf("process is attached to memory");
    x=(int*)shared_mem;
    printf("x[0]= %d  x[1]= %d",x[0],x[1]);
    shmdt(shared_mem);
    struct shmid_ds *buf;
    
    shmctl(shmid,IPC_RMID,0);
    printf("Shared Memory Destroyed");
    return 0;
}
