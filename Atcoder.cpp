#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n; cin>>n;
	map<int,int>mp;
	for(int i=0;i<n;i++){
		int x; cin>>x;
		mp[x]++;
	}
	int c=0;
	for(auto it:mp){
		c+=it.first+1;
	}
	cout<<c<<endl;
	return 0;
}