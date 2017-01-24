// RandomUsername (Nikola Jovanovic)
// Kosaraju's algorithm for finding strongly connected
// components in a directed graph
// O(V + E) - one DFS

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
    vector<int> adj; // original graph
    vector<int> adjT; // reversed graph
    int comp; // index of the SCC this node belongs to
    bool visited; // for DFS1
};

node g[MAXN];
int n, m;
stack<int> s; // all graph nodes ordered by DFS exit time
vector<vector<int>> components;

// First DFS, establish an ordering of the nodes that 
// corresponds to the topological sorting of the component graph
// there is an edge comp(u) -> comp(v) => dfsExit(u) > dfsExit(v) 
void DFS1(int curr)
{
    g[curr].visited = true;
    for(int nxt : g[curr].adj)
    {
        if(!g[nxt].visited)
        {
            DFS1(nxt);
        }
    }
    // We put nodes with highest DFS exit time on top of the stack
    s.push(curr); 
}

// Second DFS, build components
void DFS2(int curr, int componentIdx, vector<int> *component)
{
    g[curr].comp = componentIdx;
    component -> push_back(curr);
    for(int nxt : g[curr].adjT)
    {
        if(g[nxt].comp == 0)
        {
            DFS2(nxt, componentIdx, component);
        }
    }
}

int kosaraju()
{
    for(int i = 1; i <= n; i++)
    {
        if(!g[i].visited)
        {
            DFS1(i);
        }
    }
    int numComponents = 0;
    while(!s.empty())
    {
        if(g[s.top()].comp == 0)
        {
            vector<int> component;
            DFS2(s.top(), ++numComponents, &component);
            components.push_back(component);
        }
        s.pop();
    }
    return numComponents;
}

void printComponents()
{
    printf("\nComponents:");
    for(auto &component : components)
    {
        printf("\n");
        for(int v : component)
        {
            printf("%d ", v);
        }
    }
    printf("\nTotal number of strongly connected components: %d.\n", components.size());
}

bool sinkComponent[MAXN]; // needed for BOTTOM
// Testing
// Test problem: http://www.spoj.com/problems/BOTTOM/
int main()
{
    while(1)
    {
        scanf("%d", &n);
        if(n == 0)
        {
            return 0;
        }
        scanf("%d", &m);
        // Reset
        components.clear();
        for(int i = 1; i <= n; i++)
        {
            g[i].adj.clear();
            g[i].adjT.clear();
            g[i].comp = 0;
            g[i].visited = false;
            sinkComponent[i] = true;
        }
        for(int i = 0; i < m; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            g[u].adj.push_back(v);
            g[v].adjT.push_back(u);
        }
        kosaraju();
        // printComponents();
        // BOTTOM: we are looking for all SCCs with 0 
        // outgoing edges in the component graph
        // (NB this can be done more easily by exploiting Kosaraju's toposort)
        for(int i = 1; i <= n; i++)
        {
            for(int v : g[i].adj)
            {
                if(g[i].comp != g[v].comp)
                {
                    // Cross-component edge
                    sinkComponent[g[i].comp] = false;
                }
            }
        }
        for(int i = 1; i <= n; i++)
        {
            if(sinkComponent[g[i].comp])
            {
                printf("%d ", i);
            }
        }
        printf("\n");
    }
    return 0;
}

/*
Test case from https://en.wikipedia.org/wiki/Strongly_connected_component
8 14
1 2
2 3
3 4
4 3
5 1
2 5
2 6
3 7
4 8
8 4
5 6
6 7
7 6
8 6
*/