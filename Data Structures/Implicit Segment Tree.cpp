// RandomUsername (Nikola Jovanovic)
// Implicit Segment Tree
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

    // The range assigned to this node
    int l, r;

    // Children
    node* left;
    node* right;

    node()
    {
        NULLNODE = false;
        left = right = NULL;
        val = INF;
    }
    node(bool nullNode)
    {
        NULLNODE = nullNode;
        left = right = NULL;
        val = INF;
    }

    int len(){ return r - l + 1; }
    int middle(){ return (r+l) / 2; }
};

// Merging function, RMinQ
void segMerge(node* ret, node* a, node* b)
{
    if(a -> NULLNODE && b -> NULLNODE)
    {
        ret -> NULLNODE = true;
        return;
    }
    else ret -> NULLNODE = false;
    if(a -> NULLNODE) ret -> val = b -> val;
    if(b -> NULLNODE) ret -> val = a -> val;
    ret -> val = min(a -> val, b -> val);
}

// Root
node* root;

// Build
void init(int n)
{
    root = new node();
    root -> l = 1;
    root -> r = n;
}

// If we're trying to access a nonexistent node, we create it
void newNode(node* curr, char dir)
{
    node* chd = new node();
    if(dir == 'l')
    {
        chd -> l = curr -> l;
        chd -> r = curr -> middle();
        curr -> left = chd;
    }
    else
    {
        chd -> l = curr -> middle() + 1;
        chd -> r = curr -> r;
        curr -> right = chd;
    }
}

// a[qi] = v
void update(node* curr, int qi, node* v, int l, int r)
{
    if(l == r)
    {
        // Leaf node
        curr -> val = v -> val;
        return;
    }
    // Nonexistent nodes
    if(curr -> left == NULL) newNode(curr, 'l');
    if(curr -> right == NULL) newNode(curr, 'r');
    // Standard segtree stuff
    if(qi <= mid) update(curr -> left, qi, v, l, mid);
    else update(curr -> right, qi, v, mid+1, r);
    segMerge(curr, curr -> left, curr -> right);
}

// min[lq..rq]?
node* query(node* curr, int lq, int rq, int l, int r)
{
    if(lq <= l && rq >= r)
    {
        // Canonic cover
        return curr;
    }
    // Nonexistent nodes
    if(curr -> left == NULL) newNode(curr, 'l');
    if(curr -> right == NULL) newNode(curr, 'r');
    // Standard segtree stuff
    node* ret = new node(true);
    if(lq <= mid) segMerge(ret, ret, query(curr -> left, lq, rq, l, mid));
    if(rq > mid) segMerge(ret, ret, query(curr -> right, lq, rq, mid+1, r));
    return ret;
}

// Testing
// Test problem: http://www.spoj.com/problems/KGSS/
int main()
{
    int n, q, kom, qi, lq, rq, vv;
    node* v = new node();

    scanf("%d", &n);
    init(n);
    scanf("%d", &q);
    for(int i = 1; i <= q; i++)
    {
        scanf("%d", &kom);
        if(kom == 1)
        {
            // update
            scanf("%d %d", &qi, &vv);
            v -> val = vv;
            update(root, qi, v, 1, n);
        }
        else if(kom == 2)
        {
            // query
            scanf("%d %d", &lq, &rq);
            v = query(root, lq, rq, 1, n);
            printf("%d\n", v -> val);
        }
    }
    return 0;
}
