#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
#define int long long int
#define fass ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define random(l, r,T) uniform_int_distribution<T>(l, r)(rng)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int m=1e9+7;
int stoi(string &s){ int num=0; for(int i=0;i<s.size();i++)num=num*10+(s[i]-'0'); return num;}
int power(int a,int b){ int ans=1; while(b!=0){ if((b&1)) ans=(ans*a)%m; b/=2; a=(a*a)%m; } return ans;}
const int N=2e5+10;
vector<int>adj[N];
vector<int>color(N,0),dp(N,0);
set<int>*color_set[N];
void dfs(int node,int par)
{
    int max_size=-1,node_value=-1;
    for(auto child:adj[node])
    {
        if(child!=par)
        {
            dfs(child,node);
            if(dp[child]>max_size)
            {
                max_size=dp[child];
                node_value=child;
            }
        }
    }
    if(max_size==-1)
    {
        color_set[node]=new set<int>();
    }
    else{
        color_set[node]=color_set[node_value];
    }
    (*color_set[node]).insert(color[node]);
    for(auto child:adj[node])
    {
        if(child!=par && child!=node_value)
        {
            for(int ele:(*color_set[child]))(*color_set[node]).insert(ele);
        }
    }
    dp[node]=(*color_set[node]).size();

}
signed main()
{
    // freopen("output.txt", "w", stdout);
    fass
    int t=1;
    // cin>>t;
    while(t--)
    {
        /*Always set upper_bound in binary search carefully*/
        int n;cin>>n;
        // vector<int>c(n+1);
        int k=1;
        for(int i=1;i<=n;i++)
        {
            cin>>color[i];
        }
        for(int i=1;i<n;i++)
        {
            int a,b;
            cin>>a>>b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        dfs(1,-1);
        for(int i=1;i<=n;i++)cout<<dp[i]<<" ";
        cout<<endl;
    }
    return 0;
}