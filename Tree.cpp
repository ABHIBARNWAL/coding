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


const int N = 2e5 + 1;
int parent[N][20];
int level[N];
int path[N];
int inT[N],outT[N];
int weight[N];
int segmentTree[8*N];
vector<int>eulerPath;
void dfs(int src, int par, vector<int> tree[])
{
	for (int &child : tree[src])
	{
		if (par != child)
		{
			level[child] = level[src] + 1;
			dfs(child, src, tree);
		}
	}
}
void findPath(int src,int par,vector<int>tree[])
{
	for(int child:tree[src])
	{
		if(par!=child)
		{
			findPath(child,src,tree);
			path[src]+=path[child];
		}
	}
}
void binaryLifting(int src, int par, vector<int> tree[])
{
	parent[src][0] = par;
	for (int i = 1; i <= 19; i++)
	{
		if (parent[src][i - 1] != -1)
			parent[src][i] = parent[parent[src][i - 1]][i - 1];
	}
	for (int &child : tree[src])
	{
		if (par != child)
		{
			binaryLifting(child, src, tree);
		}
	}
}
int findKthParent(int node, int k)
{
	if (k == 0 || node == -1)
		return node;
	int value = 0;
	for (int i = 19; i >= 1; i--)
	{
		int val = (1 << i);
		if ((val & k) > 0)
		{
			value = i;
			break;
		}
	}
	return (findKthParent(parent[node][value], k - (1 << value)));
}
int findLowestCommonAncestor(int u,int v)
{
	if(level[u]>level[v])
	u=findKthParent(u,level[u]-level[v]);
	else if(level[v]>level[u])
	v=findKthParent(v,level[v]-level[u]);
	if(u==v)
	return u;
	else return LCA(u,v);
}
int LCA(int u, int v)
{
	if (parent[u][0] == parent[v][0])
	{
		return parent[u][0];
	}
	int k = 0;
	for (int i = 19; i >= 0; i--)
	{
		if (parent[u][i] != parent[v][i])
		{
			k = i;
			break;
		}
	}
	return LCA(parent[u][k], parent[v][k]);
}
void eulerTour(int src,int par,vector<int>tree[])
{
	eulerPath.push_back(src);
	for(int child:tree[src])
	{
		if(child!=par)
		eulerTour(child,src,tree);
	}
	eulerPath.push_back(src);
}
void build(int id,int low,int high)
{
	if(low==high){
		segmentTree[id]=weight[eulerPath[low]];
		return;
	}
	int mid=(low+high)/2;
	build(2*id+1,low,mid);
	build(2*id+2,mid+1,high);
	segmentTree[id]=max(segmentTree[2*id+1],segmentTree[2*id+2]);
}
void update(int id,int low,int high,int p)
{
	if(low==high)
	{
		segmentTree[id]=weight[eulerPath[low]];
		return;
	}
	int mid=(low+high)/2;
	if(p<=mid)
	update(2*id+1,low,mid,p);
	else 
	update(2*id+2,mid+1,high,p);
	segmentTree[id]=max(segmentTree[2*id+1],segmentTree[2*id+2]);
}
int query(int id,int low,int high,int l,int r)
{
	if(high<l||low>r)
	return 0;
	if(low>=l && high<=r)
	return segmentTree[id];
	int mid=(low+high)/2;
	int left=query(2*id+1,low,mid,l,r);
	int right=query(2*id+2,mid+1,high,l,r);
	return max(left,right);
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
		memset(parent, -1, sizeof(parent));
		memset(level, 0, sizeof(level));
		memset(path, 0, sizeof(path));
		int n, q;
		cin >> n >> q;
		vector<int> adj[n + 1];
		for(int i=1;i<=n;i++)
		cin>>weight[i];
		for (int i = 2; i <= n; i++)
		{
			int x, y;
			cin >> x >> y;
			adj[y].push_back(x);
			adj[x].push_back(y);
		}
		// binaryLifting(1, -1, adj);
		// dfs(1, -1, adj);
		eulerTour(1,-1,adj);
		memset(inT,-1,sizeof(inT));
		for(int i=0;i<eulerPath.size();i++){
			// cout<<eulerPath[i]<<" ";
			if(inT[eulerPath[i]]==-1)
			inT[eulerPath[i]]=i;
			else 
			outT[eulerPath[i]]=i;
		}
		build(0,0,(2*n)-1);
		while(q--)
		{
			int p;cin>>p;
			if(p==1)
			{
				int s,x;
				cin>>s>>x;
				weight[s]=x;
				update(0,0,(2*n)-1,inT[s]);
				update(0,0,(2*n)-1,outT[s]);
			}
			else{
				int a,b;
				cin>>a>>b;
				cout<<query(0,0,(2*n)-1,inT[1],inT[s])<<endl;
			}
		}
		
		
	}
	return 0;
}