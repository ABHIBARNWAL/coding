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
signed main()
{
    // freopen("output.txt", "w", stdout);
    fass
    int t=1;cin>>t;
    while(t--)
    {
        int n,m;cin>>n>>m;
        vector <int> v(n+1,n);
        while(m--){
            int a,b;cin>>a>>b;
            
            v[min(a,b)] = min(max(a,b)-1,v[min(a,b)]);

        
        }
        for(int i=n-1;i>=1;i--){
            v[i] = min(v[i],v[i+1]);
        }

        //for(int i=1;i<=n;i++)cout<<v[i]<<' ';cout<<endl;
        int ans = 0;
        for(int i=1;i<=n;i++){
          
            int x = i;
            int y = v[i];
            if(x!=y)ans +=  y-x;
        }
        ans+=n;
        cout<<ans<<"\n";
    }
    return 0;
} 