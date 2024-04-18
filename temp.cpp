#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
#define int long long int
#define fass                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define random(l, r, T) uniform_int_distribution<T>(l, r)(rng)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int mod = 1e9 + 7;
int stoi(string &s)
{
    int num = 0;
    for (int i = 0; i < s.size(); i++)
        num = num * 10 + (s[i] - '0');
    return num;
}
int power(int a, int b)
{
    int ans = 1;
    while (b != 0)
    {
        if ((b & 1))
            ans = (ans * a) % mod;
        b /= 2;
        a = (a * a) % mod;
    }
    return ans;
}
void asort(vector<int> &v) { sort(v.begin(), v.end()); }
void dsort(vector<int> &v) { sort(v.begin(), v.end(), greater<int>()); }
bool dfs(int i, int par, set<int> adj[], vector<int> &vis, vector<int> &v)
{
    vis[i] = 1;
    for (auto &node : adj[i])
    {
        if (vis[node] == 0)
        {
            v.push_back(node);
            bool flag = dfs(node, i, adj, vis, v);
            if (flag)
                return true;
            v.pop_back();
        }
        else if (par != node)
        {
            v.push_back(node);
            return true;
        }
    }
    return false;
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    fass int t = 1;
    cin >> t;
    while (t--)
    {
        /*Always set upper_bound in binary search carefully*/
        int n;
        cin >> n;
        set<int> adj[n + 1];
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
            adj[i].insert(a[i]);
            adj[a[i]].insert(i);
        }
        // stack<int>st;
        // vector<int>vis2(n+1,0);
        // for(int i=1;i<=n;i++)
        // {
        //     if(vis2[i]==0)dfs1(i,adj,vis2,st);
        // }
        vector<int> vis(n + 1, 0);
        map<int, int> mp;
        for (int i = 1; i <= n; i++)
        {
            if (vis[i] == 0)
            {
                vector<int> v;
                v.push_back(i);
                bool flag = dfs(i, -1, adj, vis, v);

                if (flag)
                {
                    // for (int i = 0; i < v.size(); i++)
                    // {
                    //     cout << v[i] << " ";
                    // }
                    // cout << endl;
                    mp[2]++;
                }
                else
                    mp[1]++;
            }
        }
        int mini = 0;
        if (mp[1] > 0)
            mini += 1;
        cout << mini + mp[2] << " " << mp[1] + mp[2] << endl;
    }
    return 0;
}