// RandomUsername (Nikola Jovanovic)
// Kruskal's Minimum Spanning Tree algorithm
// O(E * logE)
// Works for disconnected graphs

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

// algorithms/Data Structures/Disjoint Set (Union Find).cpp
class DSU
{
    private:
        struct node
        {
            int rnk, p; // Rank and parent
        };
        node uf[MAXN];
        int n;

        // Find the root of a node
        int root(int x)
        {
            // Path compression
            if( uf[x].p != x )
                uf[x].p = root( uf[x].p );
            return uf[x].p;
        }

    public:
        // Init
        void init(int n)
        {
            this -> n = n;
            for(int i = 1; i <= n; i++)
            {
                // Every vertex is a head of its own component and all ranks are zero
                uf[i].p = i;
                uf[i].rnk = 0;
            }
        }

        // Connect two nodes - returns true if connected, false if already connected
        bool connect(int x, int y)
        {
            int xroot = root(x);
            int yroot = root(y);
            if(xroot == yroot)
                return false;

            // Union by rank
            if( uf[xroot].rnk < uf[yroot].rnk )
                uf[xroot].p = yroot;
            else if( uf[yroot].rnk < uf[xroot].rnk )
                uf[yroot].p = xroot;
            else
                uf[yroot].p = xroot, uf[xroot].rnk++;
            return true;
        }
};

struct edge
{
    int a, b;
    int cost;
    const bool operator< (const edge &other)
    const
    {
        return cost < other.cost;
    }
};

DSU dsu;
vector<edge> edges;

int kruskal(int n)
{
    dsu.init(n);
    int mstSum = 0;
    sort(edges.begin(), edges.end());
    for(edge &e : edges)
    {
        if(dsu.connect(e.a, e.b))
        {
            mstSum += e.cost;
        }
    }
    return mstSum;
}

// Testing
// Test problem: http://www.spoj.com/problems/BLINNET/
int main()
{
    int t;
    scanf("%d", &t);
    for(int tt = 1; tt <= t; tt++)
    {
        int n;
        scanf("%d", &n);
        edges.clear();
        for(int i = 1; i <= n; i++)
        {
            char dummy[20];
            scanf("%s", dummy);
            int sz;
            scanf("%d", &sz);
            for(int j = 1; j <= sz; j++)
            {
                int v, w;
                scanf("%d %d", &v, &w);
                edges.push_back({i, v, w});
            }
        }
        printf("%d\n", kruskal(n));
    }
    return 0;
}
