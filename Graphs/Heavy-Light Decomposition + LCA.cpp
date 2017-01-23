// RandomUsername (Nikola Jovanovic)
// Heavy-Light Decomposition with Lowest Common Ancestor application
// HLD: O(E + V)
// LCA: O(logV)

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

using namespace std;

struct node
{
    vector<int> adj; // Edges from this node
    int parent;
    int level;
    int nodesUnder; // Number of nodes in this node's subtree
    int chainTop; // Top of this node's heavy chain
};

// The graph
node g[MAXN];

// DFS as a first step in HLD
int DFS(int curr, int level)
{
    g[curr].level = level;
    g[curr].nodesUnder = 1;
    int sz = g[curr].adj.size();
    for(int i = 0; i < sz; i++)
    {
        g[curr].nodesUnder += DFS(g[curr].adj[i], level + 1); // DP
    }
    return g[curr].nodesUnder;
}

void HLD(int curr, int chainTop)
{
    g[curr].chainTop = chainTop;
    int sz = g[curr].adj.size();
    for(int i = 0; i < sz; i++)
    {
        // If we use a light edge, our nodesUnder should be (at least) halved
        // This can guarantee at most logV nodes on every root->leaf path
        int nxt = g[curr].adj[i];
        if((1.0 * g[nxt].nodesUnder) > (0.5 * g[curr].nodesUnder))
        {
            HLD(nxt, chainTop); // Continue the heavy chain
        }
        else
        {
            HLD(nxt, nxt); // New heavy chain
        }
    }
}

// Computing the lowest common ancestor for nodes a and b
int LCA(int a, int b)
{
    int aTop = g[a].chainTop;
    int bTop = g[b].chainTop;
    // If a and b are on the same heavy chain we return the higher node
    if(aTop == bTop)
    {
        if(g[a].level < g[b].level)
        {
            return a;
        }
        else
        {
            return b;
        }
    }
    // If a and b are not on the same heavy chain we can jump to the lower
    // chain top and traverse ONE light edge => O(logV) in total
    if(g[aTop].level > g[bTop].level)
    {
        return LCA(g[aTop].parent, b);
    }
    else
    {
        return LCA(a, g[bTop].parent);
    }
}

// Testing
// Test problem: http://www.spoj.com/problems/LCA/
int main()
{
    int t;
    scanf("%d", &t);
    for(int tt = 1; tt <= t; tt++)
    {
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
        {
            g[i].adj.clear();
            g[i].parent = g[i].nodesUnder = g[i].chainTop = 0;
            g[i].level = -1;
        }
        for(int i = 1; i <= n; i++)
        {
            int sz, v;
            scanf("%d", &sz);
            for(int j = 1; j <= sz; j++)
            {
                scanf("%d", &v);
                g[i].adj.push_back(v);
                g[v].parent = i;
            }
        }
        // Find the root
        int root = 0;
        for(int i = 1; i <= n; i++)
        {
            if(g[i].parent == 0)
            {
                root = i;
                break;
            }
        }
        DFS(root, 0);
        HLD(root, root);
        // Queries
        int q;
        scanf("%d", &q);
        printf("Case %d:\n", tt);
        int a, b;
        for(int i = 1; i <= q; i++)
        {
            scanf("%d %d", &a, &b);
            printf("%d\n", LCA(a, b));
        }
    }
    return 0;
}
