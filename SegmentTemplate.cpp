#include <bits/stdc++.h>
using namespace std;
#define int long long int
const int N=1e5;
const int N2=4*N;
vector<vector<int>>tre(N2,vector<int>(20,0));
vector<int>arr(N);
const int mod=1e9+7;
class Segment{
    public:
    
    vector<int>merge(vector<int>&a,vector<int>&b)
    {
        vector<int>ans(20,0);
        for(int i=0;i<20;i++)
        {
            ans[i]+=a[i];
            ans[i]+=b[i];
        }
        return ans;
    }
    void build(int id,int low,int high)
    {

        if(low==high){
            tre[id][arr[low]-1]++;
            return;
        }
        int mid=(low+high)/2;
        build(2*id+1,low,mid);
        build(2*id+2,mid+1,high);
        tre[id]=merge (tre[2*id+1],tre[2*id+2]);
    }
    void update(int id,int low,int high,int p,int val)
    {
        if(low==high){
            tre[id][arr[p]-1]--;
            tre[id][val-1]++;
            return;
        }
        int mid=(low+high)/2;
        if(p<=mid)update(2*id+1,low,mid,p,val);
        else update(2*id+2,mid+1,high,p,val);
        tre[id]=merge(tre[2*id+1],tre[2*id+2]);
    }
    vector<int>query(int id,int low,int high,int l,int r)
    {
        if(low>r||high<l){
            vector<int>temp(20,0);
            return temp ;
        }
        // cout<<low<<" "<<high<<endl;
        if(low>=l && high<=r)return tre[id];
        int mid=(low+high)/2;
        vector<int>left=query(2*id+1,low,mid,l,r);
        vector<int>right=query(2*id+2,mid+1,high,l,r);
        vector<int> ans=merge(left,right);
        return ans;
    }

};
signed main()
{
    Segment S;
    int n;cin>>n;
    for(int i=0;i<n;i++)cin>>arr[i];
    S.build(0,0,n-1);
    int q;
    cin>>q;
    int ans=0;
    while(q--)
    {
        int p;cin>>p;
        if(p==2)
        {
            int l,r;cin>>l>>r;
            l--;
            S.update(0,0,n-1,l,r);

        }
        else{
            int l,r;
            cin>>l>>r;
            l--;
            r--;
            vector<int>v=S.query(0,0,n-1,l,r);
            sort(v.begin(),v.end());
            for(int i=1;i<20;i++)
            {
                v[i]-=v[i-1];
                v[i-1]=0;
            }
            bool flag=true;
            for(int i=0;i<20;i++)
            {
                if(v[i]>0)flag=false;
            }
            if(flag)
            {
                ans=((ans%mod)+ ((r-l+1)%mod))%mod;
            }
        }
    }
    cout<<ans<<endl;
}