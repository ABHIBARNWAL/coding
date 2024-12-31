#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define fass                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
const int N = 2e5 + 1;
struct Node
{
    bool islazy = false;
    bool isInc = false;
    bool isEq = false;
    int inct = 0;
    int sett = INT_MAX;
    int incx = 0;
    int setx = 0;
    int sum = 0;
};
vector<int> arr(N);
Node tree[4 * N];
void push(int id, int low, int high)
{
    if (tree[id].islazy)
    {
        int sett = tree[id].sett, inct = tree[id].inct;
        if (sett < inct)
        {
            tree[id].sum = (high - low + 1) * tree[id].setx;
            tree[id].sum += ((high - low + 1) * tree[id].incx);
            if (low != high)
            {
                tree[2 * id + 1].inct = tree[2 * id + 2].inct = tree[id].inct;
                tree[2 * id + 1].sett = tree[2 * id + 2].sett = tree[id].sett;
                tree[2 * id + 1].incx = tree[2 * id + 2].incx = tree[id].incx;
                tree[2 * id + 1].setx = tree[2 * id + 2].setx = tree[id].setx;
                tree[2 * id + 1].islazy = tree[2 * id + 2].islazy = true;
            }
        }
        else if(sett!=INT_MAX && sett>inct)
        {
            tree[id].sum = (high - low + 1) * tree[id].setx;
            if (low != high)
            {
                tree[2 * id + 1].sett = tree[2 * id + 2].sett = tree[id].sett;
                tree[2 * id + 1].setx = tree[2 * id + 2].setx = tree[id].setx;
                tree[2 * id + 1].islazy = tree[2 * id + 2].islazy = true;
            }
        }
        else{
            tree[id].sum += ((high - low + 1) * tree[id].incx);
            if(low!=high)
            {
                int mid=(low+high)/2;
                
                
            }
        }
    }
    tree[id].islazy = false;
    tree[id].sett = INT_MAX;
    tree[id].inct = 0;
    tree[id].incx = 0;
    tree[id].setx = 0;
}

void merge(int id, int left, int right)
{
    tree[id].sum = tree[left].sum + tree[right].sum;
    return;
}
void build(int id, int low, int high)
{
    if (low == high)
    {
        tree[id].sum = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * id + 1, low, mid);
    build(2 * id + 2, mid + 1, high);
    merge(id, 2 * id + 1, 2 * id + 2);
}
void update1(int id, int low, int high, int l, int r, int v, int &timer)
{
    push(id, low, high);
    if (low > r || high < l)
        return;
    if (low >= l && high <= r)
    {
        tree[id].islazy = true;
        tree[id].incx += v;
        tree[id].inct = timer;
        push(id, low, high);
        return;
    }
    int mid = (low + high) / 2;
    update1(2 * id + 1, low, mid, l, r, v, timer);
    update1(2 * id + 2, mid + 1, high, l, r, v, timer);
    merge(id, 2 * id + 1, 2 * id + 2);
}
void update2(int id, int low, int high, int l, int r, int v, int &timer)
{
    push(id, low, high);
    if (low > r || high < l)
        return;
    if (low >= l && high <= r)
    {
        tree[id].islazy = true;
        tree[id].setx = v;
        tree[id].sett = timer;
        push(id, low, high);
        return;
    }
    int mid = (low + high) / 2;
    update2(2 * id + 1, low, mid, l, r, v, timer);
    update2(2 * id + 2, mid + 1, high, l, r, v, timer);
    merge(id, 2 * id + 1, 2 * id + 2);
}
int query(int id, int low, int high, int l, int r)
{
    push(id, low, high);
    if (low > r || high < l)
        return 0;
    if (low >= l && high <= r)
    {
        return tree[id].sum;
    }
    int mid = (low + high) / 2;
    int left = query(2 * id + 1, low, mid, l, r);
    int right = query(2 * id + 2, mid + 1, high, l, r);
    return (left + right);
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
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        build(0, 0, n - 1);
        int timer = 0;
        while (q--)
        {
            int p;
            cin >> p;
            timer++;
            if (p == 1)
            {
                int a, b, v;
                cin >> a >> b >> v;
                a--;
                b--;
                update1(0, 0, n - 1, a, b, v, timer);
            }
            else if (p == 2)
            {
                int a, b, v;
                cin >> a >> b >> v;
                a--;
                b--;
                update2(0, 0, n - 1, a, b, v, timer);
            }
            else
            {
                int a, b;
                cin >> a >> b;
                a--;
                b--;
                int x = query(0, 0, n - 1, a, b);
                cout << x << endl;
            }
        }
    }
    return 0;
}