#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>

void*func(void *a)
{
    int *x=(int *)a;
    int times=x[1];
    int ch=x[0];
    for(int i=0;i<times;i++)
    printf("%d",ch);
    printf("\n");
}

int main()
{
    pthread_t threadId[2];
    int arr[2];
    for(int i=0;i<2;i++)
    {
        arr[0]=i;
        printf("The number of times u want to print %d\n",i);
        scanf("%d",&arr[1]);
        if(pthread_create(&threadId[i],NULL,func,arr)<0)
        {
            printf("Thread Not Created\n");
            exit(0);
        }
        else{
            pthread_join(threadId[i],NULL);
        }
    }
    // for(int i=0;i<2;i++)
    // {
    //     pthread_join(threadId[i],NULL);
    // }
    return 0;
}