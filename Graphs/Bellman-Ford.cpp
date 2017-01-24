// RandomUsername (Nikola Jovanovic)
// Bellman-Ford single source shortest paths
// O(V*E)
// Handles negative weight edges

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
#define MAXN 1005

using namespace std;

struct edge
{
    int a, b;
    int cost;
};

vector<edge> edges;
int D[MAXN];
int from[MAXN];

bool BF(int n, int startNode)
{
    // Init
    for(int i = 1; i <= n; i++)
    {
        D[i] = INF;
    }
    D[startNode] = 0;
    from[startNode] = startNode;
    // Relax all edges n - 1 times
    for(int i = 1; i <= n; i++)
    {
        for(edge &e : edges) 
        {
            if(D[e.a] + e.cost < D[e.b])
            {
                if(i == n)
                {
                    // If anything can be relaxed in n-th
                    // iteration => there are negative cycles
                    return false;
                }
                D[e.b] = D[e.a] + e.cost;
                from[e.b] = e.a;
            }
        }
    }
    return true;
}

// Testing
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges.push_back({u, v, w});
        edges.push_back({v, u, w}); // Bidirectional
    }
    if(!BF(n, 1))
    {
        printf("Negative cycles exist!\n");
        return 0;
    }
    for(int i = 1; i <= n; i++)
    {
        printf("Distance from 1 to %d = %d\n", i, D[i]);
    }
    return 0;
}
