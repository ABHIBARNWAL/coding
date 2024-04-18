#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
#define int long long int
#define fass ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
int dp[3001][3001];
const int maxn=1e18;
int sqr(int x)
{
    return x*x;
}
// int solve(int i,int j,int k,vector<int>&prefix,int n)
// {
//     if(i==n)
//     {
//         if(k==1)
//         {
//             return sqr(prefix[i]-prefix[j-1]);
//         }
//         else{
//             return maxn;
//         }
//     }
//     if(k==0)
//     {
//         if(j==n+1)return 0;
//         return maxn;
//     }
//     if(dp[i][j]!=-1)return dp[i][j];
//     int ans=maxn;
//     ans=min(ans,solve(i+1,i+1,k-1,prefix,n)+sqr(prefix[i]-prefix[j-1]));
//     ans=min(ans,solve(i+1,j,k,prefix,n));
//     dp[i][j]=ans;
//     return ans;
// }
void dnc(int i,int l,int r,int optl,int optr,vector<int>&prefix)
{
    if(l>r)return;
    pair<int,int>ans={maxn,l};
    int mid=(l+r)/2;
    for(int j=optl;j<min(mid,optr+1);j++)
    {
        ans=min(ans,{sqr(prefix[mid]-prefix[j])+dp[i-1][j],j});
    }
    dp[i][mid]=ans.first;
    dnc(i,l,mid-1,optl,ans.second,prefix);
    dnc(i,mid+1,r,ans.second,optr,prefix);
}
signed main()
{
    // freopen("output.txt", "w", stdout);
    int n,k;
    cin>>n>>k;
    vector<int>v(n),prefix(n+1,0);
    for(int i=0;i<n;i++)cin>>v[i];
    for(int i=0;i<n;i++)prefix[i+1]=prefix[i]+v[i];
    // memset(dp,-1,sizeof(dp));
    for(int i=0;i<=n;i++)dp[0][i]=maxn;
    int ans;
    dp[0][0]=0;
    for(int i=1;i<=k;i++)
    {
        dnc(i,1,n,0,n-1,prefix);
    }
    // for(int i=0;i<=k;i++)
    // {
    //     for(int j=1;j<=n;j++)
    //     {
    //         cout<<setw(20)<<dp[i][j];
    //     }
    //     cout<<endl;
    // }
    cout<<dp[k][n]<<endl;
    return 0;
}
