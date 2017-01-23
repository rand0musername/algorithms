// RandomUsername (Nikola Jovanovic)
// Floyd-Warshall all pairs shortest path
// O(V^3)
// Can detect negative cycles

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
    int a, b; // Endpoints
    int cost;
};

struct node
{
    vector<edge> adj;
};

// The graph
node g[MAXN];
int D[MAXN][MAXN];
int path[MAXN][MAXN];

bool FW(int n)
{
    // Init
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            D[i][j] = INF;
        }
        D[i][i] = 0;
    }
    for(int i = 1; i <= n; i++)
    {
        int sz = g[i].adj.size();
        for(int j = 0; j < sz; j++)
        {
            edge e = g[i].adj[j];
            D[i][e.b] = e.cost; 
        }
    }
    // Using first k nodes to find a better route from i to j
    for(int k = 1; k <= n; k++)
    {
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
               if(D[i][k] + D[k][j] < D[i][j])
               {
                    D[i][j] = D[i][k] + D[k][j];
                    // Node with the highest index on the best path from i to j
                    path[i][j] = k;
               }
            }
        }
    }
    // Detect negative cycles
    for(int i = 1; i <= n; i++)
    {
        if(D[i][i] < 0)
        {
            return false;
        }
    }
    return true;
}

vector<int> reconstruct(int a, int b)
{
    vector<int> ret;
    int middle = path[a][b];
    if(middle == 0)
    {
        ret.push_back(a);
    }
    else
    {
        vector<int> left = reconstruct(a, middle);
        vector<int> right = reconstruct(middle, b);
        ret.insert(ret.end(), left.begin(), left.end());
        left.push_back(middle);
        ret.insert(ret.end(), right.begin(), right.end());
    }
    return ret;
}

// Testing
// Test problem: http://www.spoj.com/problems/LCA/
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g[u].adj.push_back({u, v, w});
        // g[v].adj.push_back({v, u, w}); // Undirected graph
    }
    if(!FW(n))
    {
        printf("Negative cycles exist!\n");
        return 0;
    }
    int a, b;
    scanf("%d %d", &a, &b);
    printf("Shortest path from %d to %d (len = %d):\n", a, b, D[a][b]);
    vector<int> v = reconstruct(a, b);
    for(int node : v)
    {
        printf("%d -> ", node);
    }
    printf("%d\n", b);
    return 0;
}
