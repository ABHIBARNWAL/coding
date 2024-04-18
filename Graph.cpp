#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
#define int long long int
#define fass ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define random(l, r,T) uniform_int_distribution<T>(l, r)(rng)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int m=1e9+7;
int stoi(string &s){ int num=0; for(int i=0;i<s.size();i++)num=num*10+(s[i]-'0'); return num;}
int power(int a,int b){ int ans=1; while(b!=0){ if((b&1)) ans=(ans*a)%m; b/=2; a=(a*a)%m; } return ans;}
const int N=5e4+10;
vector<int>adj[N];
set<int>*st[N];
vector<bitset<N>>dp(N);
void dfs(int node,vector<int>&vis,stack<int>&st)
{
    vis[node]=true;
    for(int child:adj[node])
    {
        if(!vis[child])dfs(child,vis,st);
    }
    st.push(node);
}
void Reach(int node,vector<int>&vis)
{
    // cout<<node<<" ";
    vis[node]=true;
    int maxi=-1,nd=-1;
    vector<int>childs,vis_child;
    for(int child:adj[node])
    {
        if(!vis[child]){
            childs.push_back(child);
            Reach(child,vis);
            if((*st[child]).size()>maxi)
            {
                maxi=child;
                nd=child;
            }
        }
        else{
            vis_child.push_back(child);
        }
    }
    if(maxi==-1)
    {
        st[node]=new set<int>();
    }
    else{
        st[node]=st[nd];
    }
    (*st[node]).insert(node);
    for(int child:childs)
    {
        if(child!=nd)
        {
            for(int ele:(*st[child]))(*st[node]).insert(ele);
        }
    }
    for(int ele:vis_child)
    {
        (*st[node]).insert(ele);
    }
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
        int n,m,q;
        cin>>n>>m>>q;
        for(int i=0;i<m;i++)
        {
            int x,y;
            cin>>x>>y;
            adj[x].push_back(y);
        }
        stack<int>s;
        vector<int>vis(n+1,0);
        for(int i=1;i<=n;i++)
        {
            if(!vis[i])dfs(i,vis,s);
        }
        vector<int>v;
        while(!s.empty())
        {
            v.push_back(s.top());
            s.pop();
        }
        for(int i=n-1;i>=0;i--)
        {
            int ele=v[i];
            dp[ele][ele]=1;
            for(int val:adj[ele])dp[ele]=dp[ele]|dp[val];
        }
        for(int i=1;i<=q;i++)
        {
            int a,b; cin>>a>>b;
            if(dp[a][b]==1)cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
        // cout<<endl;
    }
    return 0;
}