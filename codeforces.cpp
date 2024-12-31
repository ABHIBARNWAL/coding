#include <bits/stdc++.h>
using namespace std;
#define fass                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
const int N = 2e5 + 1;
vector<int> tree(16 * N,0);
int mat[1000][1000];
void build(int id, int lowR, int highR, int lowC, int highC)
{
    if (lowR == highR && lowC == highC)
    {
        tree[id] = mat[lowR][lowC];
        return;
    }
    int midR = (lowR + highR) / 2;
    int midC = (lowC + highC) / 2;
    if (lowR != highR && lowC != highC)
    {
        build(2 * id + 1, lowR, midR, lowC, midC);
        build(2 * id + 2, lowR, midR, midC + 1, highC);
        build(2 * id + 3, midR + 1, highR, lowC, midC);
        build(2 * id + 4, midR + 1, highR, midC + 1, highC);
        tree[id] = 0;
        for (int i = 1; i <= 4; i++)
            tree[id] += tree[2 * id + i];
    }
    else if (lowR == highR)
    {
        build(2 * id + 3, lowR, highR, lowC, midC);
        build(2 * id + 4, lowR, highR, midC + 1, highC);
        tree[id] = 0;
        for (int i = 3; i <= 4; i++)
            tree[id] += tree[2 * id + i];
    }
    else
    {
        build(2 * id + 3, lowR, midR, lowC, highC);
        build(2 * id + 4, midR + 1, highR, lowC, highC);
        tree[id] = 0;
        for (int i = 3; i <= 4; i++)
            tree[id] += tree[2 * id + i];
    }
}
void update(int id, int lowR, int highR, int lowC, int highC, int x, int y)
{
    if (lowR == highR && lowC == highC)
    {
        tree[id] = 1 - mat[lowR][lowC];
        return;
    }
    int midR = (lowR + highR) / 2;
    int midC = (lowC + highC) / 2;
    if (lowR != highR && lowC != highC)
    {
        if (x <= midR)
        {
            if (y <= midC)
                update(2 * id + 1, lowR, midR, lowC, midC,x,y);
            else
                update(2 * id + 2, lowR, midR, midC + 1, highC,x,y);
        }
        else
        {
            if (y <= midC)
                update(2 * id + 3, midR + 1, highR, lowC, midC,x,y);
            else
                update(2 * id + 4, midR + 1, highR, midC + 1, highC,x,y);
        }
        tree[id] = 0;
        for (int i = 1; i <= 4; i++)
            tree[id] += tree[2 * id + i];
    }
    else if (lowR == highR)
    {
        if (y <= midC)
            update(2 * id + 3, lowR, highR, lowC, midC,x,y);
        else
            update(2 * id + 4, lowR, highR, midC + 1, highC,x,y);
        tree[id] = 0;
        for (int i = 3; i <= 4; i++)
            tree[id] += tree[2 * id + i];
    }
    else
    {
        if (x <= midR)
            update(2 * id + 3, lowR, midR, lowC, highC,x,y);
        else
            update(2 * id + 4, midR + 1, highR, lowC, highC,x,y);
        tree[id] = 0;
        for (int i = 3; i <= 4; i++)
            tree[id] += tree[2 * id + i];
    }
}
int query(int id, int lowR, int highR, int lowC, int highC, int lR, int rR, int lC, int rC)
{
    if (lowR > rR || highR < lR || lowC>rC || highC<lC)
        return 0;
    if (lowR >= lR && highR <= rR && lowC >= lC && highC <= rC)
    {
        return tree[id];
    }
    int midR = (lowR + highR) / 2;
    int midC = (lowC + highC) / 2;
    int ans = 0;
    if (lowR != highR && lowC != highC)
    {
        ans += query(2 * id + 1, lowR, midR, lowC, midC, lR, rR, lC, rC);
        ans += query(2 * id + 2, lowR, midR, midC + 1, highC, lR, rR, lC, rC);
        ans += query(2 * id + 3, midR + 1, highR, lowC, midC, lR, rR, lC, rC);
        ans += query(2 * id + 4, midR + 1, highR, midC + 1, highC, lR, rR, lC, rC);
    }
    else if (lowR == highR)
    {
        ans += query(2 * id + 3, lowR, midR, lowC, midC, lR, rR, lC, rC);
        ans += query(2 * id + 4, lowR, midR, midC + 1, highC, lR, rR, lC, rC);
    }
    else
    {
        ans += query(2 * id + 3, midR + 1, highR, lowC, midC, lR, rR, lC, rC);
        ans += query(2 * id + 4, lowR, midR, midC, highC, lR, rR, lC, rC);
    }
    return ans;
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
        {
            for (int j = 0; j < n; j++)
            {
                char x;
                cin >> x;
                if (x == '.')
                    mat[i][j] = 0;
                else
                    mat[i][j] = 1;
            }
        }
        build(0, 0, n - 1,0,n-1);
        while (q--)
        {
            int c; cin>>c;
            if(c==1){
            int l, r;
            cin >> l >> r;
            l--;
            r--;
                update(0, 0, n - 1, 0,n-1,l, r);
            }
            else{
                int a,b,c,d;
                cin>>a>>b>>c>>d;
                a--;
                b--;
                c--;
                d--;
                cout<<query(0,0,n-1,0,n-1,a,c,b,d)<<endl;
            }
        }
    }
    return 0;
}