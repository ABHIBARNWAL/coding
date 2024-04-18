#include<stdio.h>
#include<stdlib.h>
FILE *fp;
int dp[1001][1001][2];
int max(int a,int b)
{
    if(a>b)return a;
    return b;
}
int solve_DnC(int l,int h,int b[],int s[],int c,int n)
{
    int maxi=0;
    if(l==h)
    {
        for(int i=l;i<n;i++)maxi=max(maxi,s[i]);
        int x=c/b[l];
        return(x*(maxi-b[l]));
    }
    int mid=(l+h)/2;
    maxi=0;
    int left=solve_DnC(l,mid,b,s,c,n);
    int right=solve_DnC(mid+1,h,b,s,c,n);
    return(max(left,right));
}
int solve_op(int n,int b[],int s[],int c)
{
    int suf[n];
    suf[n-1]=s[n-1];
    for(int i=n-2;i>=0;i--)
    suf[i]=max(suf[i+1],s[i]);
    int ans=0,x;
    for(int i=0;i<n;i++)
    {
        x=c/b[i];
        ans=max(ans,x*(suf[i]-b[i]));
    }
    return ans;
}
int multi_trans(int i,int j,int p,int n,int b[],int s[],int c)
{
    // freopen("output.txt","w",stdout);1
    if(j==n){
        if(p==1)
        {
            if(i<n)
            return(c%b[i]);
            else return 0;
        }
        else return c;
    }
    // if(dp[i][j][p]!=-1)return dp[i][j][p];
    fprintf(fp,"%d->%d\n",i,c);
    int ans=0;
    if(p==0)
    {
        
        ans=max(ans,multi_trans(i,i,1,n,b,s,c));
        ans=max(ans,multi_trans(i+1,i+1,p,n,b,s,c));

    }
    else
    {
        int x=c/b[i];
        int r=c%b[i];
        int nc=x*(s[j]-b[i])+r;
        ans=max(ans,multi_trans(i,j+1,1,n,b,s,c));
        ans=max(ans,multi_trans(j+1,j+1,0,n,b,s,nc));
    }
    return(dp[i][j][p]=ans);
}
int main()
{
    int n,c;
    printf("Enter the number of Products: ");
    scanf("%d",&n);
    int b[n],s[n];
    for(int i=0;i<n;i++)scanf("%d",&b[i]);
    for(int i=0;i<n;i++)scanf("%d",&s[i]);
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++){
        dp[i][j][0]=dp[i][j][1]=-1;
        }
    }
    printf("Enter the capacity: ");
    scanf("%d",&c);
    // int ans=solve_DnC(0,n-1,b,s,c,n);
    fp=fopen("output.txt","w");
    int ans=multi_trans(0,0,0,n,b,s,c);
    // for(int i=0;i<n;i++)
    // {
    //     for(int j=0;j<n;j++)
    //     {
    //         printf("(%d->%d, %d->%d)\n",i,dp[i][j][0],j,dp[i][j][1]);
    //     }
    // }
    printf("The max_profit:%d",ans);
}