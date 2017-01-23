// RandomUsername (Nikola Jovanovic)
// Dijkstra's algorithm
// Finding shortest paths from one node: O(E log V + V log V)
// Doesn't work with negative edge weights

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
};

struct node
{
    vector<edge> adj;
    int dist; // Distance from the starting node
    int from; // Possible path recontruction
    bool visited;
};

struct data
{
    int idx; // Node index
    int dist; // Distance to this node
    const bool operator< (const data &other) 
    const
    {
        return dist > other.dist;
    }
};

// The graph
node g[MAXN];

// Dijkstra's algorithm from startNode to endNode
int dijkstra(int n, int startNode, int endNode)
{
    for(int i = 1; i <= n; i++)
    {
        g[i].dist = INF;
    }

    g[startNode].dist = 0;
    priority_queue<data> pq;
    pq.push({startNode, 0});
    while(!pq.empty() && !g[endNode].visited)
    {
        data curr = pq.top();
        pq.pop();
        if(!g[curr.idx].visited)
        {
            g[curr.idx].visited = true;
            int sz = g[curr.idx].adj.size();
            for(int i = 0; i < sz; i++)
            {
                int nxt = g[curr.idx].adj[i].b;
                int cost = g[curr.idx].adj[i].cost;
                if(!g[nxt].visited && g[curr.idx].dist + cost < g[nxt].dist)
                {
                    g[nxt].dist = g[curr.idx].dist + cost;
                    g[nxt].from = curr.idx;
                    pq.push({nxt, g[nxt].dist});
                }
            }
        }
    }
    return g[endNode].dist;
}

// Testing
// Test problem: http://www.spoj.com/problems/EZDIJKST/
int main()
{
    int t;
    scanf("%d", &t);
    for(int tt = 1; tt <= t; tt++)
    {
        int n, m;
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i++)
        {
            g[i].adj.clear();
            g[i].visited = false;
            g[i].dist = INF;
            g[i].from = -1;
        }
        for(int i = 1; i <= m; i++)
        {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            g[u].adj.push_back({u, v, w});
            //g[v].adj.push_back({v, u, w}); // Undirected graph
        }
        int A, B;
        scanf("%d %d", &A, &B);
        int dist = dijkstra(n, A, B);
        if(dist == INF) 
        {
            printf("NO\n");
        }
        else
        {
            printf("%d\n", dist);
        }
    }
    return 0;
}
