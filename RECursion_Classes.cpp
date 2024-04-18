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
const int m = 1e9 + 7;
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
            ans = (ans * a) % m;
        b /= 2;
        a = (a * a) % m;
    }
    return ans;
}
signed main()
{
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
    fass int t = 1;
    cin >> t;
    while (t--)
    {
        /*Always set upper_bound in binary search carefully*/
        int n, x;
        cin >> n >> x;
        vector<int>a(n+1);
        for (int i = 1; i <= n; i++)
        {
            int k;
            cin >> k;
            a[i]=k;
        }
        int ans = 0;
        vector<int> vis(n + 1, 0);
        // cout<<q.size()<<endl;
        // for(int i=1;i<=n;i++)
        // {
        //     int ind=a[i]+i;
        //     bool flag=false;
        //     while(ind<=n)
        //     {
                
        //         if(ind==x){
        //             break;
        //         }
        //         ind=a[ind]+ind;
        //     }
        //     if(ind==x)flag=true;
        //     if(flag)ans++;
        // }
        for(int i=1;i<=n;i++)
        {
            if(vis[i]==0)
            {
                int ind=a[i]+i;
                bool flag=false;
                int c=0;
                while(ind<=n)
                {
                    vis[ind]=1;
                    if(ind==x)
                    {
                        flag=true;
                        break;
                    }
                     c++;
                    ind=a[ind]+ind;
                }
                if(ind==x)
                {
                    flag=true;
                    c++;
                }
                if(flag)ans+=c;
            }
        }
        if(x<=n)ans++;
        cout<<ans<<endl;
    }
    return 0;
}