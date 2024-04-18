#include <stdio.h>
int p[1001];
struct Node
{
    int val = 0;
    int n = 0;
};
typedef struct Node node;
node a[1001][10001];
void merge(int low,int high,int a[])
{
    int len=(high-low+1);
    int na[len];
    int mid=(low+high)/2;
    int i=0,j=low,k=mid+1;
    while(j<=mid && k<=high){
        if(a[j]>a[k]){
            na[i]=a[j];
            j++;
        }
        else{
            na[i]=a[k];
            k++;
        }
        i++;
    }
    while(j<=mid)
    {
        na[i]=a[j];
        j++;
        i++;
    }
    while(k<=high)
    {
        na[i]=a[k];
        k++;
        i++;
    }
    i=0,j=low;
    while(i<len && j<=high)
    {
        a[j]=na[i];
        i++;
        j++;
    }
}
void merge_sort(int low,int high,int a[])
{
    if(low==high)return;
    int mid=(low+high)/2;
    merge_sort(low,mid,a);
    merge_sort(mid+1,high,a);
    merge(low,high,a);
}
int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);
    merge_sort(0,n-1,p);
    printf("\n");
    node t[k];
    int mini = 10000001, indx = -1, indy;
    for (int i = 0; i < k; i++)
    {
        a[i][0].val = p[i];
        a[i][0].n=i+1;
        t[i].val = p[i];
        t[i].n = 1;
        if (mini >t[i].val)
        {
            indx = i;
            mini = t[i].val;
        }
    }
    for (int i = k; i < n; i++)
    {
        // printf("%d %d\n",indx, t[indx].n);
        a[indx][t[indx].n].val = p[i];
        a[indx][t[indx].n].n=i+1;
        t[indx].val += p[i];
        t[indx].n+=1;
        mini=1000001;indx = -1;
        for (int j = 0; j < k; j++)
        {
            if (mini > t[j].val)
            {
                indx = j;
                mini = t[j].val;
            }
        }
    }
    int sum=0,wt=0;
    for(int i=0;i<k;i++)
    {
        int ti=0;
        printf("counter %d:",i+1);
        for(int j=0;j<t[i].n;j++)
        {
            printf("%d(%d) ",a[i][j].n,a[i][j].val);
            wt+=ti;
            ti+=a[i][j].val;
        }
        if(ti>sum)sum=ti;
        printf("\n");
    }
    printf("Cafe closes at time: %d\n",sum);
    printf("Total waiting time: %d\n",wt);
}