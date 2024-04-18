#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vll vector <ll>
#define random(l,r,T) uniform_int_distribution<T>(l,r)(rng)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


// *     Test case generator     **
void test(string path,int i)
{
    freopen(path.c_str(), "w", stdout); // stdout <- file stream
    // cout <- object that writes in stdout
    // if we link stdout to the target file, cout can write in that file,
    // input file generate
    if(i == 0)
    {
        cout << "3" << endl;
        cout << "5 5" << endl;
        cout << "2 3 4 1 5" << endl;
        cout << "4 4" << endl;
        cout << "1 2 1 4" << endl;
        cout << "5 4" << endl;
        cout << "2 3 4 3 8" << endl;
    }
    else if(i<3){
        int t = 100;
        assert(t>=2 && t<=100);
        cout<<t<<endl;
        while(t--){
            int n = random(1,15,int);
            int k=random(1,15,int);
            assert(n>=1 && n<=200);
            assert(k>=1 && k<=200);
            cout<<2*n<<' '<<2*k<<endl;
            for(int j = 0;j<2*n;j++){
                int ch = random(1,15,int);
                assert(ch>=1 && ch<=2e5);
                cout<<ch<<' ';
            }
            cout<<endl;
        }
    }
    else if(i<8){
        int t = 1000;
        assert(t>=2 && t<=1000);
        cout<<t<<endl;
        for (int j = 0; j < t; j++)
        {
            int n = random(1, 100, int);
            int k = random(1, 100, int);
            assert(n>=1 && n<=2e5);
            assert(n>=1 && n<=2e5);
            cout << 2*n <<' '<< 2*k<<endl;
            for (int e = 0; e < 2*n; e++)
            {
                int ch = random(1,100,int);
                assert(ch>=1 && ch<=2e5);
                cout<<ch<<' ';
            }
            cout << endl;
        }
    }
    else if(i<12){
        int t = 100;
        assert(t>=2 && t<=1000);
        cout<<t<<endl;
        int sum = 0;
        for (int j = 0; j < t; j++)
        {
            int n = random(1000, 2000, int);
            assert(n>=1000 && n<=2000);
            int k = random(1000, n, int);
            assert(k>=1000 && k<=2000);
            cout << 2*n <<' '<<k<< endl;
            sum += n;
            assert(sum<=2e5 && sum>=1);
            for (int e = 0; e < 2*n; e++)
            {
                char ch = random(1,100,int);
                assert(ch>=1 && ch<=2000);
                cout<<ch<<' ';
            }
            cout << endl;
        }
    }
    else if(i==12){
        int t = 1;
        assert(t>=1 && t<=1000);
        cout<<t<<endl;
        for (int j = 0; j < t; j++)
        {
            int n = 20000;
            int k=random(100,20000,int);
            assert(k>=100 && k<=20000);
            cout << 2*n <<' '<< 2*k<<endl;
            for (int f = 0; f < 2*n; f++)
            {
                int ch = random(1,2e5,int);
                assert(ch>=1 && ch<=2e5);
                cout<<ch<<' ';
            }
            cout << endl;
        }
    }
    else if(i == 13){
        int t = 1;
        assert(t>=1 && t<=1000);
        cout << t << endl;
        for (int j = 0; j < t; j++)
        {
            int n = 10000;
            assert(n>=1 && n<=2e5);
            int k=random(100,20000,int);
            assert(k>=100 && k<=20000);
            cout << n <<' '<< 2*k<< endl;
            for (int f = 0; f < n; f++)
            {
                int ch=random(1,2e5,int);
                assert(ch>=1 && ch<=2e5);
                cout<<ch<<' ';
            }
            cout << endl;
        }
    }
    else{
        int t = 1;
        assert(t>=1 && t<=1000);
        cout << t << endl;
        for (int j = 0; j < t; j++)
        {
            int n = 100;
            assert(n>=1 && n<=2e5);
            cout << 2*n << ' '<<2*n-1<< endl;
            for (int k = 0; k < 2*n; k++)
            {
                int ch = random(1,200,int);
                assert(ch>=1 && ch<=200);
                cout<<ch<<' ';
            }
            cout << endl;
        }
    }
}

// *     CODE     **
void solve(string ipath,string opath)
{
    freopen(ipath.c_str(), "r", stdin);
    freopen(opath.c_str(), "w", stdout);
    // solution starts here
      ll t;cin>>t;
    while(t--){
        ll n,target;cin>>n>>target;
        vector<ll>a(n+1);
        for(ll i=1;i<=n;i++) cin>>a[i];
        ll paths=0;
        for(ll i=1;i<=n;i++){
            for(ll j=i;j<=n;j+=a[j]){
                if(j==target) paths++;
            }
        }
        cout<<paths<<'\n';
    }
}

int main()
{
    int p = 10;
    for(int i=0;i<p;i++)
    {
        string path = to_string(i);
        if(i < 10) path = "0" + path; // "01" "02" "10"
        string ipath = "Minimized_the_GCD/Input/input" + path + ".txt"; 
        test(ipath,i);
        string opath = "Minimized_the_GCD/Ouput/input" + path + ".txt";
        solve(ipath,opath);
    }
}