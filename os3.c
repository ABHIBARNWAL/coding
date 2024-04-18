#include<stdio.h>        // printf scanf
#include<unistd.h>       // slepp
#include <sys/types.h>   // pid_t
#include<sys/wait.h>     // wait
#include <signal.h>      // signal kill
#include<stdlib.h>       
int main()
{
    int i;
    freopen("output.txt","w",stdout);
    while((i>=2) && (!fork()))
    {
        printf("\nH");
        i++;
    }
    int _=1;
    printf("%d",_);
    printf("\nhello");
    // for(;;);
}