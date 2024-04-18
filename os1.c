#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }
    system("top");
    int i = 0;
    for(int i=1;i<argc;i++) {
        printf("%s\n",argv[i]);
    }

    return 0;
}
