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
    printf("shared memory created");
    x=(int*)shared_mem;
    x[0]=1;
    x[1]=6;
    for(;;);
    shmdt(shared_mem);
    return 0;
}
