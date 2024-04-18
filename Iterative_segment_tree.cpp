#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=100000+10;

struct Node{
    int mi;
    int count;
    Node(int a, int b){
        mi=a;
        count=b;
    }
    Node(){
        mi=INT_MAX;
        count=0;
    }
};

Node tree[4*N];

Node merge(Node a, Node b)
{
    if(a.mi == b.mi){
        return Node(a.mi, a.count + b.count);
    }
    else if(a.mi < b.mi){
        return a;
    }
    return b;
}

void build(vector<int>&nums, int l, int r, int node)  
{  
    if(l==r){
        tree[node]=Node(nums[l],1);
        return;
    }
    int mid=(l+r)/2;
    build(nums,l,mid,2*node);
    build(nums,mid+1,r,2*node+1);
    tree[node]=merge(tree[2*node],tree[2*node+1]);
} 

void update(int node, int l, int r, int x, int v, vector<int>&nums)
{
	if (l == r)
	{
		tree[node]=Node(v,1);
		nums[l]=v;
		return;
	}
	int m = (l + r) / 2;
    if(x<=m)
	update(2 * node, l, m, x, v,nums);
    else
	update(2 * node + 1, m + 1, r, x, v,nums);
	tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}
Node query(int node, int l, int r, int lq, int rq)
{
	if (r<lq || l>rq)
	{
		return Node();
	}
	if(lq <= l && rq >= r){
	    return tree[node];
	}
	int m = (l + r) / 2;
	Node lc = query(2 * node, l, m, lq, rq);
	Node rc = query(2 * node + 1, m + 1, r, lq, rq);
	return merge(lc, rc);
}

int32_t main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n,m;
    cin>>n>>m;
    vector<int>nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    build(nums, 0, n-1, 1);
    int x,l,r;
    for(int i=0;i<m;i++){
        cin>>x>>l>>r;
        if(x==1){
            update(1,0,n-1,l, r, nums);
        }
        else{
            Node x=query(1,0,n-1,l, r-1);
            cout<<x.mi<<" "<<x.count<<endl;
        }
    }
    return 0;
}