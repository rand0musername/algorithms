// RandomUsername (Nikola Jovanovic)
// Depth-First Search + finding the number of connected components

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
    int level;
};

node g[MAXN];

void DFS(int curr, int level)
{
    g[curr].visited = true;
    g[curr].level = level;
    printf("Node %d on level %d\n", curr, g[curr].level);
    int sz = g[curr].adj.size();
    for(int i = 0; i < sz; i++)
    {
        int nxt = g[curr].adj[i];
        if(!g[nxt].visited)
        {
            DFS(nxt, level + 1);
        }
    }
}

int components(int n)
{
    int ret = 0;
    for(int i = 1; i <= n; i++)
    {
        if(!g[i].visited)
        {
            DFS(i, 0);
            ret++;
        }
    }
    return ret;
}

// Testing
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].adj.push_back(v);
        g[v].adj.push_back(u);
    }
    printf("Number of components: %d\n", components(n));
    return 0;
}
