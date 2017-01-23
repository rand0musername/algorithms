// RandomUsername (Nikola Jovanovic)
// Topological Sorting
// O(V + E) for any toposort (queue)
// O(VlogV + E) for lexicographically smallest toposort (priority queue)
// DAG <=> No directed cycles <=> Has at least one toposort

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
    int indegree;
    bool visited;
};

node g[MAXN];

vector<int> toposort(int n)
{
    vector<int> ret;
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i = 1; i <= n; i++)
    {
        if(g[i].indegree == 0)
        {
            pq.push(i);
        }
    }
    while(!pq.empty())
    {
        int curr = pq.top();
        pq.pop();
        ret.push_back(curr);
        int sz = g[curr].adj.size();
        for(int i = 0; i < sz; i++)
        {
            int nxt = g[curr].adj[i];
            g[nxt].indegree--;
            if(g[nxt].indegree == 0)
            {
                pq.push(nxt);
            }
        }
    }
    return ret;
}

// Testing
// Test problem: http://www.spoj.com/problems/TOPOSORT/
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].adj.push_back(v);
        g[v].indegree++;
    }
    vector<int> topo = toposort(n);
    if(topo.size() < n - 1)
    {
        printf("Sandro fails.\n"); // Cycles
        return 0;
    }
    for(int node : topo)
    {
        printf("%d ", node);
    }
    return 0;
}
