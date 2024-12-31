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
int a[201][201];
const int INF = INT_MAX;
void hungarianMethod(int n, int m)
{
    vector<int> u(n + 1), v(m + 1), p(m + 1), way(m + 1);
    for (int i = 1; i <= n; ++i)
    {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(m + 1, INF);
        vector<char> used(m + 1, false);
        do
        {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1;
            for (int j = 1; j <= m; ++j)
                if (!used[j])
                {
                    int cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j])
                        minv[j] = cur, way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j], j1 = j;
                }
            for (int j = 0; j <= m; ++j)
                if (used[j])
                    u[p[j]] += delta, v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do
        {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    vector<int> ans(n + 1);
    int cost=0;
    for (int j = 1; j <= m; ++j){
        cost+=a[p[j]][j];
        ans[p[j]] = j;
    }
    cout<<cost<<endl;
    for(int i=1;i<=n;i++){
        cout<<i<<" "<<ans[i]<<endl;
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
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                cin >> a[i][j];
        }
        hungarianMethod(n, n);
    }
    return 0;
}