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
const int mod=1e9+7;
int stoi(string &s){ int num=0; for(int i=0;i<s.size();i++)num=num*10+(s[i]-'0'); return num;}
int power(int a,int b){ int ans=1; while(b!=0){ if((b&1)) ans=(ans*a)%mod; b/=2; a=(a*a)%mod; } return ans;}
void asort(vector<int>&v){ sort(v.begin(),v.end()); }
void dsort(vector<int>&v){ sort(v.begin(),v.end(),greater<int>());}
signed main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    fass
    int t=1;cin>>t;
    while(t--)
    {
        /*Always set upper_bound in binary search carefully*/
    }
    return 0;
}