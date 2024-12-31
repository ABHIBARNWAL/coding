#include <bits/stdc++.h>
using namespace std;
// #define int long long int
#define fass                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
const int N = 2e5 + 10;
int maxN;
vector<int> adj[N];
int value[N];
int parent[N];
int level[N];
int subsize[N];
int heavy[N];
int head[N];
int pos[N];
int linearTree[N];
int idx;
int stree[10 * N];
void build(int id, int low, int high)
{
    if (low == high)
    {
        stree[id] = linearTree[low];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * id + 1, low, mid);
    build(2 * id + 2, mid + 1, high);
    stree[id] = max(stree[2 * id + 1], stree[2 * id + 2]);
}
void update(int id, int low, int high, int p, int v)
{
    if (low == high)
    {
        stree[id] = v;
        return;
    }
    int mid = (low + high) / 2;
    if (p <= mid)
        update(2 * id + 1, low, mid, p, v);
    else
        update(2 * id + 2, mid + 1, high, p, v);
    stree[id] = max(stree[2 * id + 1], stree[2 * id + 2]);
}
int query(int id, int low, int high, int l, int r)
{
    if (low > r || high < l)
        return 0;
    if (low >= l && high <= r)
        return stree[id];
    int mid = (low + high) / 2;
    int left = query(2 * id + 1, low, mid, l, r);
    int right = query(2 * id + 2, mid + 1, high, l, r);
    return max(left, right);
}
void supdate(int k, int value)
{
    k += maxN;
    stree[k] = value;
    k /= 2;
    while (k >0)
    {
        stree[k] = max(stree[2 * k], stree[2 * k + 1]);
        k /= 2;
    }
}
int squery(int l, int r)
{
    int ans = 0;
    l += maxN;
    r += maxN;
    while (l <= r)
    {
        if (l & 1)
        {
            ans = max(ans, stree[l]);
            l++;
        }
        if (~r & 1)
        {
            ans = max(ans, stree[r]);
            r--;
        }
        l /= 2;
        r /= 2;
    }
    return ans;
}
void dfs(int src, int par)
{
    for (int &child : adj[src])
    {
        if (par != child)
        {
            parent[child] = src;
            level[child] = level[src] + 1;
            dfs(child, src);
            subsize[src] += subsize[child];
            if (heavy[src] == -1 || subsize[heavy[src]] < subsize[child])
                heavy[src] = child;
        }
    }
    subsize[src]++;
}

void dfsHLD(int src, int par, int chain)
{
    head[src] = chain;
    pos[src] = idx;
    linearTree[idx] = value[src];
    idx++;
    if (heavy[src] != -1)
        dfsHLD(heavy[src], src, chain);
    for (int &child : adj[src])
    {
        if (child != par && child != heavy[src])
            dfsHLD(child, src, child);
    }
}

int LCA(int u, int v)
{
    while (head[u] != head[v])
    {
        // cout<<u<<" "<<v<<endl;
        if (level[head[u]] < level[head[v]])
            swap(u, v);
        u = parent[head[u]];
    }
    if (level[u] < level[v])
        return u;
    else
        return v;
}

int pathQuery(int u, int v)
{
    int ans = 0;
    while (head[u] != head[v])
    {
        if (level[head[u]] < level[head[v]])
            swap(u, v);
        // cout<<path<<" "<<v<<" "<<sum<<endl;
        ans = max(ans, squery(pos[head[u]]-1, pos[u]-1));
        u = parent[head[u]];
    }
    if (level[u] < level[v])
        ans = max(ans, squery(pos[u]-1, pos[v]-1));
    else
        ans = max(ans, squery(pos[v]-1, pos[u]-1));
    return ans;
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    // fass 
    int t = 1;
    // cin>>t;
    while (t--)
    {
        /*Always set upper_bound in binary search carefully*/
        int n, q;
        cin >> n >> q;
        for (int i = 1; i <= n; i++)
            cin >> value[i];
        for (int i = 2; i <= n; i++)
        {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        memset(parent, -1, sizeof(parent));
        memset(level, 0, sizeof(level));
        memset(subsize, 0, sizeof(subsize));
        memset(heavy, -1, sizeof(heavy));
        dfs(1, -1);
        memset(head, -1, sizeof(head));
        memset(pos, -1, sizeof(pos));
        idx = 1;
        dfsHLD(1, -1, 1);
        // build(0,1,n);
        int x = (ceil(log2(n)));
        maxN = (1 << x);
        for (int i = 1; i <= n; i++)
            supdate(i-1, linearTree[i]);
        while (q--)
        {
            int c, a, b;
            cin >> c >> a >> b;
            if (c == 1)
            {
                supdate(pos[a]-1, b);
            }
            else
            {
                cout << pathQuery(a, b) << " ";
            }
        }
        cout <<endl;
    }
    return 0;
}