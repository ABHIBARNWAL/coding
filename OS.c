#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int sum=0;
int arr[10]={1,2,3,4,5,6,7,8,9,10};
void*thread_code(void *a)
{
    int ind=*((int *)a);
    int s=0;
    for(int i=ind;i<ind+5;i++)
    {
        s+=arr[i];
    }
    sum+=s;
    // printf("%d\n",s);
    // pthread_exit(&s);
}
int main()
{
    pthread_t threads[2];
    int pthread_args[2]={0,5};
    for(int i=0;i<2;i++)
    {
        pthread_create(&threads[i],NULL,thread_code,&pthread_args[i]);
    }
    void *p;
    for(int i=0;i<2;i++)
    {
        int x=pthread_join(threads[i],NULL);
        // sum+=*((int*)p);
    }
    printf("the sum of array is %d",sum);
    return 0;
}