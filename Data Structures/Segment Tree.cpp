// RandomUsername (Nikola Jovanovic)
// Segment Tree
// init: O(NlogN)
// update: O(logN)
// query: O(logN)
// N - array size

#include <bits/stdc++.h>
#define DBG false
#define debug(x) if(DBG) printf("(ln %d) %s = %d\n", __LINE__, #x, x);
#define lld long long
#define ff(i,a,b) for(int i=a; i<=b; i++)
#define fb(i,a,b) for(int i=a; i>=b; i--)
#define par pair<int, int>
#define fi first
#define se second
#define mid (l+r)/2
#define INF 1000000000
#define MAXN 100005
#define MAXLOGN 20

using namespace std;

// Node template
struct node
{
    bool NULLNODE;
    int val;
    node(){ NULLNODE = false; }
    node(bool nullNode) {NULLNODE = nullNode;}
};

// Merging function
node segMerge(node a, node b)
{
    // RMinQ
    if(a.NULLNODE) return b;
    if(b.NULLNODE) return a;
    return (a.val < b.val) ? a : b;
}

// Original array, segment tree
int a[MAXN];
node seg[MAXN*4];

// Build
void init(int idx, int l, int r)
{
    if(l == r)
    {
        // Leaf node
        seg[idx].val = a[l];
        return;
    }
    init(2*idx, l, mid);
    init(2*idx+1, mid+1, r);
    seg[idx] = segMerge(seg[2*idx], seg[2*idx+1]);
}

// a[qi] = v
void update(int qi, node v, int idx, int l, int r)
{
    if(l == r)
    {
        // Leaf node
        seg[idx] = v;
        return;
    }
    if(qi <= mid) update(qi, v, 2*idx, l, mid);
    else update(qi, v, 2*idx+1, mid+1, r);
    seg[idx] = segMerge(seg[2*idx], seg[2*idx+1]);
}

// min[lq..rq]?
node query(int lq, int rq, int idx, int l, int r)
{
    if(lq <= l && rq >= r)
    {
        // Canonic cover
        return seg[idx];
    }
    node ret(true);
    if(lq <= mid) ret = segMerge(ret, query(lq, rq, 2*idx, l, mid));
    if(rq > mid) ret = segMerge(ret, query(lq, rq, 2*idx+1, mid+1, r));
    return ret;
}

// Testing
// Test problem: http://www.spoj.com/problems/KGSS/
int main()
{
    int n, q, kom, qi, lq, rq;
    node v;

    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    init(1, 1, n);
    scanf("%d", &q);
    for(int i = 1; i <= q; i++)
    {
        scanf("%d", &kom);
        if(kom == 1)
        {
            // update
            scanf("%d %d", &qi, &v.val);
            update(qi, v, 1, 1, n);
        }
        else if(kom == 2)
        {
            // query
            scanf("%d %d", &lq, &rq);
            v = query(lq, rq, 1, 1, n);
            printf("%d\n", v.val);
        }
    }
    return 0;
}
