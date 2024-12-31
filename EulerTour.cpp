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
int inT[N];
int outT[N];
int prefix[N];
int color[N];
vector<int> eulerTour;
vector<int> tree[8 * N];
void dfs(int src, int par)
{
    eulerTour.push_back(src);
    for (int &child : adj[src])
    {
        if (par != child)
        {
            dfs(child, src);
        }
    }
    eulerTour.push_back(src);
}
void createEulerTour()
{
    dfs(1, -1);
    memset(inT, -1, sizeof(inT));
    memset(outT, -1, sizeof(outT));
    for (int i = 0; i < 2 * n; i++)
    {
        if (inT[eulerTour[i]] == -1)
            inT[eulerTour[i]] = i;
        else
            outT[eulerTour[i]] = i;
    }
}
void merge(int id, int left, int right)
{
    int l1 = tree[left].size();
    int l2 = tree[right].size();
    int i = 0, j = 0;
    while (i < l1 && j < l2)
    {
        if (tree[left][i] <= tree[right][j])
        {
            tree[id].push_back(tree[left][i]);
            i++;
        }
        else
        {
            tree[id].push_back(tree[right][j]);
            j++;
        }
    }
    while (i < l1)
    {
        tree[id].push_back(tree[left][i]);
        i++;
    }
    while (j < l2)
    {
        tree[id].push_back(tree[right][j]);
        j++;
    }
}
void build(int id, int low, int high, vector<int> &a)
{
    if (low == high)
    {
        tree[id].push_back(a[low]);
        return;
    }
    int mid = (low + high) / 2;
    build(2 * id + 1, low, mid, a);
    build(2 * id + 2, mid + 1, high, a);
    merge(id, 2 * id + 1, 2 * id + 2);
}
int query(int id, int low, int high, int l, int r)
{
    if (high < l || low > r)
        return 0;
    if (low >= l && high <= r)
    {
        return tree[id].end() - upper_bound(tree[id].begin(), tree[id].end(), r);
    }
    int mid = (low + high) / 2;
    int left = query(2 * id + 1, low, mid, l, r);
    int right = query(2 * id + 2, mid + 1, high, l, r);
    return (left + right);
}
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    fass int t = 1;
    // cin>>t;
    while (t--)
    {
        /*Always set upper_bound in binary search carefully*/
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> color[i];
        for (int i = 2; i <= n; i++)
        {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        map<int, int> mp;
        vector<int> nextRight(2 * n);
        for (int i = 2 * n - 1; i >= 0; i--)
        {
            if (mp[color[eulerTour[i]]] == 0)
            {
                nextRight[i] = 2 * n;
                mp[color[eulerTour[i]]] = i;
            }
            else
            {
                nextRight[i] = mp[color[eulerTour[i]]];
                mp[color[eulerTour[i]]] = i;
            }
        }
        // printv(eulerTour);
        build(0, 0, 2 * n - 1, nextRight);
        // printv(tree[0]);
        for (int i = 1; i <= n; i++)
        {
            cout << query(0, 0, 2 * n - 1, inT[i], outT[i]) << " ";
            // cout<<endl;
        }
        cout << endl;
    }
    return 0;
}