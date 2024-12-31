#include<stdio.h>
int main()
{
    char word[10000];
    scanf("%s",word);
    int i=0;
    while(word[i]!='\0')
    {
        int x=word[i]-'A';
        x=(x+2)%26;
        word[i]='A'+x;
        i++;
    }
    printf("%s",word);
}