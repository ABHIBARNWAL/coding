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
    fass int t = 1;
    cin >> t;
    while (t--)
    {
        /*Always set upper_bound in binary search carefully*/
        int n;
        cin >> n;
        string s;
        cin >> s;
        map<char, set<int>> mp[n];
        map<char, set<int>> mp2;
        for (int i = 0; i < n; i++)
        {
            string s1;
            cin >> s1;
            for (int j = 0; j < s1.size(); j++)
            {
                mp[i][s1[j]].insert(j);
                mp2[s1[j]].insert(i);
            }
        }
        int ans=0;
        for (int i = 0; i < n; i++)
        {
            int id = -1,j=0;
            while (j < s.size())
            {
                auto it = mp[i][s[j]].lower_bound(id);
                if (it == mp[i][s[j]].end())
                {
                    break;
                }
                else
                {
                    id = (*it) + 1;
                    j++;
                }
            }
            // cout<<"id: "<<id<<endl;
            if (j == s.size())
            {
                ans += n;
            }
            else
            {
                vector<int> temp;
                for (auto it : mp2[s[j]])
                {
                    temp.push_back(it);
                }
                int c=0;
                // cout<<temp.size()<<endl;
                for (int k = 0; k < temp.size(); k++)
                {
                    id = -1;
                    int l=j;
                    while (l < s.size())
                    {
                        auto it = mp[temp[k]][s[l]].lower_bound(id);
                        if (it == mp[temp[k]][s[l]].end())
                        {
                            break;
                        }
                        else
                        {
                            id = (*it) + 1;
                            l++;
                        }
                    }
                    if(l==s.size()){
                        // cout<<temp[k]<<endl;
                        c++;
                    }
                }
                // cout<<"i: "<<i<<"c: "<<c<<endl;
                ans+=c;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}