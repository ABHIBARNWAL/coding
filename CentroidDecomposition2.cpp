#include <bits/stdc++.h>
using namespace std;
// #define int long long int
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
void env(vector<int> &a)
{
    for (int i = 0; i < a.size(); i++)
        cin >> a[i];
}
int f(int a)
{
    if (a <= 0)
        return 0;
    int res[] = {a, 1ll, a + 1ll, 0ll};
    return res[a % 4ll];
}
int getXor(int a, int b) { return f(b) ^ f(a - 1); }
void printv(vector<int> &v)
{
    for (auto a : v)
        cout << a << " ";
    cout << endl;
}
const int N = 2e5 + 1;
vector<int> adj[N];
vector<int> vis(N, 0);
vector<int> ssze(N, 1);
vector<int> parent(N, -1);
vector<int> cnt(N, 0);
int max_depth = 0, k;
long long int ans = 0;
int calc_size(int u, int p)
{
    ssze[u] = 1;
    for (auto v : adj[u])
    {
        if (v != p && vis[v] == 0)
        {
 
            ssze[u] += calc_size(v, u);
        }
    }
    return ssze[u];
}
 
int get_centroid(int u, int p, int n)
{
    for (auto v : adj[u])
    {
        if (v != p && vis[v] == 0 && ssze[v] > (n / 2))
        {
            return get_centroid(v, u, n);
        }
    }
    return u;
}
void calc_ans(int u, int p, bool pos, int k, int depth)
{
    if (depth > k)
        return;
    max_depth = max(max_depth, depth);
    if (pos)
        ans = (ans + 0ll + cnt[k - depth]);
    else
        cnt[depth]++;
    for (auto v : adj[u])
    {
        if (v != p && vis[v] == 0)
            calc_ans(v, u, pos, k, depth + 1);
    }
}
void centroidDecomposition(int u, int par)
{
 
    int n = calc_size(u, par);
    int centroid = get_centroid(u, par, n); // find the centroid
    parent[centroid] = par;
    vis[centroid] = 1;
    max_depth = 0;
    cnt[0] = 1;
    for (auto v : adj[centroid])
    {
        if (!vis[v])
        {
            calc_ans(v, centroid, true, k, 1);
            calc_ans(v, centroid, false, k, 1);
        }
    }
    for (int i = 1; i <= max_depth; i++)
        cnt[i] = 0;
    for (auto v : adj[centroid])
    {
        if (!vis[v])
            centroidDecomposition(v, centroid);
    }
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    fass int t = 1;
    // cin >> t;
    while (t--)
    {
        /*Always set upper_bound in binary search carefully*/
        int n;
        cin >> n >> k;
        for (int i = 1; i < n; i++)
        {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        // dfs(1, -1);
        centroidDecomposition(1, -1);
        cout << ans << endl;
    }
    return 0;
}