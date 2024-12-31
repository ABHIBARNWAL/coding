#include<stdio.h>
int main()
{
    int n; scanf("%d",&n);
    int sum=0;
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        sum +=x;
    }
    if(sum%n==0)
    {
        printf("Yes\n");
    }
    else{
        int val=sum%n;
        printf("No %d",val);
    }
}