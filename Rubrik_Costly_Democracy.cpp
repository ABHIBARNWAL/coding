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
const int mod = 998244353;
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
void env(vector<int> &a)
{
    for (int i = 0; i < a.size(); i++)
        cin >> a[i];
}
void dfs(int node, int par, vector<int> adj[], vector<int> &nodes, vector<int> &dp)
{
    for (int &child : adj[node])
    {
        if (child != par)
        {
            dfs(child, node, adj, nodes, dp);
            nodes[node] += nodes[child];
            dp[node] += nodes[child] + dp[child];
        }
    }
}
void calc(int node, int par, int part, vector<int> adj[], vector<int> &dp2, vector<int> &dp1, vector<int> &nodes, int n)
{
    dp2[node] = dp1[node] + n - nodes[node] + part;
    for (int &child : adj[node])
    {
        if (child != par)
        {
            calc(child, node, dp2[node] - dp1[child] - nodes[child], adj, dp2, dp1, nodes, n);
        }
    }
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
        vector<int> nodes(n + 1);
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> nodes[i];
            sum += nodes[i];
        }
        vector<int> adj[n + 1];
        for (int i = 1; i < n; i++)
        {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        vector<int> dp1(n + 1, 0), dp2(n + 1, 0);
        dfs(1, -1, adj, nodes, dp1);
        calc(1, -1, 0, adj, dp2, dp1, nodes, sum);
        for (int i = 1; i <= n; i++)
            cout << dp2[i] << " ";
        cout << endl;
    }
    return 0;
}