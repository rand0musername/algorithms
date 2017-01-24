// RandomUsername (Nikola Jovanovic)
// Ford-Fulkerson max flow
// O(maxflow * E)

// Two variations: FF:DFS, HK:BFS
// Matching = Max Flow (With dummy S and T and unit capacities)
// Min Cut = Max Flow
// Konig's theorem (bipartite graphs): 
// Min Vertex Cover = Max Matching = N - Max Independent Set = Min Edge Cover

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
#define MAXN 305

using namespace std;

struct node
{
    vector<int> adj;
    bool visited;
};

node g[MAXN];
int cap[MAXN][MAXN]; // Capacities (regular and residual)

// Try to find a valid S->T path that increases the flow
int DFS(int curr, int T, int upMin)
{
    if(curr == T)
    {
        // Reached the sink
        return upMin;
    }
    g[curr].visited = true;
    int sz = g[curr].adj.size();
    for(int i = 0; i < sz; i++)
    {
        int nxt = g[curr].adj[i];
        if(!g[nxt].visited && cap[curr][nxt] > 0)
        {
            int flowReached = DFS(nxt, T, min(upMin, cap[curr][nxt]));
            if(flowReached > 0)
            {
                // Reached the sink, update capacities
                cap[curr][nxt] -= flowReached;
                cap[nxt][curr] += flowReached;
                g[curr].visited = false;
                return flowReached;
            }
        }
    }
    g[curr].visited = false;
    return 0;
}

int FF(int S, int T)
{
    int retFlow = 0, currFlow;
    // Get more flow while it is possible
    do
    {
        currFlow = DFS(S, T, INF);
        retFlow += currFlow;
    } 
    while(currFlow > 0);
    return retFlow;
}

// Testing
// Test problem: http://www.spoj.com/problems/QUEST4/ 
int main()
{
    int S = 0, T = 241;
    int t, n;
    scanf("%d", &t);
    for(int tt = 1; tt <= t; tt++)
    {
        // First partition: [1..120] cols
        // Second partition: [121..240] rows
        // 0 -> dummy source, 241 -> dummy sink
        for(int i = S; i <= T; i++)
        {
            g[i].adj.clear();
            for(int j = S; j <= T; j++)
            {
                cap[i][j] = 0;
            }
        }
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            x++, y++;
            // Connect x and y
            g[x].adj.push_back(y+120);
            cap[x][y+120] = 1;
            g[y+120].adj.push_back(x);
            cap[y+120][x] = 0;
            // Connect x to the source
            g[S].adj.push_back(x);
            cap[S][x] = 1;
            g[x].adj.push_back(S);
            cap[x][S] = 0;
            // Connect y to the sink
            g[y+120].adj.push_back(T);
            cap[y+120][T] = 1;
            g[T].adj.push_back(y+120);
            cap[T][y+120] = 0;
        }
        printf("%d\n", FF(S, T));
    }
    return 0;
}
// Another cool problem: SWERC 13 B