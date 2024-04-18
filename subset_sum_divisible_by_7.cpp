#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
#define int long long int
#define fass ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define random(l,r,T) uniform_int_distribution<T>(l,r)(rng)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int solve(int i,vector<int>&v,vector<vector<int>>&dp,int sum)
{
    if(i==v.size())
    {
        if(sum%7==0)return 1;
        return 0;
    }
    int r=sum%7;
    if(dp[i][r]!=-1)return dp[i][r];
    int ans=0;
    ans=solve(i+1,v,dp,sum+v[i]);
    ans+=solve(i+1,v,dp,sum);
    return(dp[i][r]=ans);
}

signed main()
{
    freopen("output.txt", "w", stdout);
    fass
    int t=1;
    while(t--)
    {
        /*Always set upper_bound in binary search carefully*/
        int n=4;
        vector<int>v(n);
        for(int i=0;i<n;i++)
        {
            cin>>v[i];
        }
        vector<vector<int>>dp(n+1,vector<int>(7,-1));
        int ans=solve(0,v,dp,0);
        cout<<ans<<endl;
    }
    return 0;
}