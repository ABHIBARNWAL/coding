#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define fass                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
int grid[1000][1000];
int tree[4000][4000];
int n;
void build_y(int idx, int lowx, int highx, int idy, int lowy, int highy)
{
    if (lowy == highy)
    {
        if (lowx == highx)
            tree[idx][idy] = grid[lowx][lowy];
        else
            tree[idx][idy] = tree[2 * idx + 1][idy] + tree[2 * idx + 2][idy];
        return;
    }
    int midy = (lowy + highy) / 2;
    build_y(idx, lowx, highx, 2 * idy + 1, lowy, midy);
    build_y(idx, lowx, highx, 2 * idy + 2, midy + 1, highy);
    tree[idx][idy] = tree[idx][2 * idy + 1] + tree[idx][2 * idy + 2];
}
void build_x(int id, int low, int high)
{
    if (low == high)
    {
        build_y(id, low, high, 0, 0, n - 1);
        return;
    }
    int mid = (low + high) / 2;
    build_x(2 * id + 1, low, mid);
    build_x(2 * id + 2, mid + 1, high);
    build_y(id, low, high, 0, 0, n - 1);
}
void update_y(int idx, int lowx, int highx, int idy, int lowy, int highy, int x, int y, int val = 0)
{
    if (lowy == highy)
    {
        if (lowx == highx){
            grid[lowx][lowy]=1-grid[lowx][lowy];
            tree[idx][idy] =  grid[lowx][lowy];
        }
        else
            tree[idx][idy] = tree[2 * idx + 1][idy] + tree[2 * idx + 2][idy];
        return;
    }
    int midy = (lowy + highy) / 2;
    if (y <= midy)
        update_y(idx, lowx, highx, 2 * idy + 1, lowy, midy, x, y, val);
    else
    update_y(idx, lowx, highx, 2 * idy + 2, midy+1, highy, x, y, val);
    tree[idx][idy] = tree[idx][2 * idy + 1] + tree[idx][2 * idy + 2];
}
void update_x(int id, int low, int high, int x, int y, int val = 0)
{
    if (low == high)
    {
        update_y(id, low, high, 0, 0, n - 1,x,y,val);
        return;
    }
    int mid = (low + high) / 2;
    if (x <= mid)
        update_x(2 * id + 1, low, mid, x, y, val);
    else
        update_x(2 * id + 2, mid + 1, high, x,y, val);
    update_y(id, low, high, 0, 0, n - 1, x, y, val);
}
int query_y(int idx, int lowx, int highx, int idy, int lowy, int highy, int ly, int ry)
{
    if (lowy > ry || highy < ly)
        return 0;
    if (lowy >= ly && highy <= ry)
    {
        return tree[idx][idy];
    }
    int midy = (lowy + highy) / 2;
    int left = query_y(idx, lowx, highx, 2 * idy + 1, lowy, midy, ly, ry);
    int right = query_y(idx, lowx, highx, 2 * idy + 2, midy + 1, highy, ly, ry);
    return (left + right);
}
int query_x(int id, int low, int high, int lx, int rx, int ly, int ry)
{
    if (low > rx || high < lx)
        return 0;
    if (low >= lx && high <= rx)
    {
        return (query_y(id, low, high, 0, 0, n - 1, ly, ry));
    }
    int mid = (low + high) / 2;
    int left = query_x(2 * id + 1, low, mid, lx, rx, ly, ry);
    int right = query_x(2 * id + 2, mid + 1, high, lx, rx, ly, ry);
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
        int q;
        cin >> n >> q;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                char x;
                cin >> x;
                if (x == '*')
                    grid[i][j] = 1;
                else
                    grid[i][j] = 0;
            }
        }
        build_x(0, 0, n - 1);
        while(q--)
        {
            int c; cin>>c;
            if(c==1){
                int x,y;
                cin>>x>>y;
                x--;
                y--;
                update_x(0,0,n-1,x,y);
            }
            else{
                int x1,y1,x2,y2;
                cin>>x1>>y1>>x2>>y2;
                x1--;
                y1--;
                x2--;
                y2--;
                cout<<query_x(0,0,n-1,x1,x2,y1,y2)<<endl;
            }
        }
    }
    return 0;
}