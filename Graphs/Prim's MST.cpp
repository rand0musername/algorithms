// RandomUsername (Nikola Jovanovic)
// Prim's Minimum Spanning Tree algorithm
// O(E * logV)
// For disconnected graphs, run Prim on every component

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

struct edge
{
    int a, b;
    int cost;
    const bool operator< (const edge &other)
    const
    {
        return cost > other.cost;
    }
};

struct node
{
    vector<edge> adj;
    bool visited;
};

node g[MAXN];

int prim(int startNode)
{
    int mstSum = 0;
    priority_queue<edge> pq;
    pq.push({startNode, startNode, 0});
    while(!pq.empty())
    {
        edge curr = pq.top();
        pq.pop();
        if(!g[curr.b].visited)
        {
            g[curr.b].visited = true;
            mstSum += curr.cost;
            int sz = g[curr.b].adj.size();
            for(int i = 0; i < sz; i++)
            {
                edge nxt = g[curr.b].adj[i];
                if(!g[nxt.b].visited)
                {
                    pq.push(nxt);
                }
            }
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
        for(int i = 1; i <= n; i++)
        {
            g[i].adj.clear();
            g[i].visited = false;
        }
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
                g[i].adj.push_back({i, v, w});
                g[v].adj.push_back({v, i, w});
            }
        }
        int ret = 0;
        for(int i = 1; i <= n; i++)
        {
            // The graph may be disconnected so we are 
            // computing the minimal spanning forest
            if(!g[i].visited)
            {
                ret += prim(i);
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}
