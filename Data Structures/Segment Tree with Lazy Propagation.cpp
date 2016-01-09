// RandomUsername (Nikola Jovanovic)
// Segment Tree with Lazy Propagation
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

// Interval sum with interval increments

// Node template
struct node
{
    bool NULLNODE;
    lld val;
    lld lazy; // Unit increment in this case
    node(){ NULLNODE = false; lazy = 0;}
    node(bool nullNode) {NULLNODE = nullNode; lazy = 0;}
};

// Merging function
node segMerge(node a, node b, lld origLazy)
{
    // Sum
    if(a.NULLNODE) return b;
    if(b.NULLNODE) return a;
    node ret;
    ret.val = a.val + b.val;
    ret.lazy = origLazy;
    return ret;
}

// Segment tree
node seg[MAXN*4];

// Build
void init(int idx, int l, int r)
{
    seg[idx].lazy = 0;
    if(l == r)
    {
        // Leaf node
        seg[idx].val = 0;
        return;
    }
    init(2*idx, l, mid);
    init(2*idx+1, mid+1, r);
    seg[idx] = segMerge(seg[2*idx], seg[2*idx+1], seg[idx].lazy);
}

// Update Propagate Reset
void upr(int idx, int l, int r)
{
    if(seg[idx].lazy != 0)
    {
        seg[idx].val += seg[idx].lazy * (r-l+1);
        if(l != r)
        {
            seg[2*idx].lazy += seg[idx].lazy;
            seg[2*idx+1].lazy += seg[idx].lazy;
        }
        seg[idx].lazy = 0;
    }
}

// a[ql..qr] += v.val
void update(int ql, int qr, node v, int idx, int l, int r)
{
    if(ql <= l && qr >= r)
    {
        // Canonic cover
        seg[idx].val += v.val * (r - l + 1);
        // Propagate this change
        if(l < r){ seg[2*idx].lazy += v.val, seg[2*idx+1].lazy += v.val;}
        return;
    }
    upr(2*idx, l, mid), upr(2*idx+1, mid+1, r);
    if(ql <= mid) update(ql, qr, v, 2*idx, l, mid);
    if(qr > mid) update(ql, qr, v, 2*idx+1, mid+1, r);
    seg[idx] = segMerge(seg[2*idx], seg[2*idx+1], seg[idx].lazy);
}

// min[lq..rq]?
node query(int lq, int rq, int idx, int l, int r)
{
    if(lq <= l && rq >= r)
    {
        // Canonic cover
        return seg[idx];
    }
    upr(2*idx, l, mid), upr(2*idx+1, mid+1, r);
    node ret(true);
    if(lq <= mid) ret = segMerge(ret, query(lq, rq, 2*idx, l, mid), 0);
    if(rq > mid) ret = segMerge(ret, query(lq, rq, 2*idx+1, mid+1, r), 0);
    return ret;
}

// Testing
// Test problem: http://www.spoj.com/problems/HORRIBLE
int main()
{
    int t, n, c;
    int kom, ql, qr, rq, lq;
    node v;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d", &n, &c);
        // The array is all zeros
        init(1, 1, n);
        while(c--)
        {
            scanf("%d", &kom);
            if(kom == 0)
            {
                // update
                scanf("%d %d %lld", &ql, &qr, &v.val);
                update(ql, qr, v, 1, 1, n);
            }
            else if(kom == 1)
            {
                // query
                scanf("%d %d", &lq, &rq);
                v = query(lq, rq, 1, 1, n);
                printf("%lld\n", v.val);
            }
        }
    }
    return 0;
}
