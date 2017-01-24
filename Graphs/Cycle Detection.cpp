// RandomUsername (Nikola Jovanovic)
// Depth-First Search for detecting cycles in a graph

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
    vector<int> adj;
    bool visited;
    bool onStack;
};

node g[MAXN];
bool directedGraph;

bool DFS(int curr, int from)
{
    g[curr].visited = true;
    g[curr].onStack = true;
    int sz = g[curr].adj.size();
    for(int i = 0; i < sz; i++)
    {
        int nxt = g[curr].adj[i];
        if(!g[nxt].visited)
        {
            if(DFS(nxt, curr))
            {
                return true;
            }
        }
        else if((directedGraph && g[nxt].onStack) || (!directedGraph && nxt != from))
        {
            return true;
        }

    }
    g[curr].onStack = false;
    return false;
}

bool cyclic(int n)
{
    for(int i = 1; i <= n; i++)
    {
        if(!g[i].visited)
        {
            if(DFS(i, 0))
            {
                return true;
            }
        }
    }
    return false;
}

// Testing
int main()
{
    scanf("%d", &directedGraph);
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].adj.push_back(v);
        if(!directedGraph)
        {
            g[v].adj.push_back(u);
        }
    }
    if(cyclic(n))
    {
        printf("Cyclic!\n");
    }
    else
    {
        printf("Not cyclic!\n");
    }
    return 0;
}
