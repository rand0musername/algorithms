// RandomUsername (Nikola Jovanovic)
// Tarjan's algorithm for finding biconnected components,
// articulation vertices and bridges in an undirected graph
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

struct edge
{
    int a, b;
};

struct node
{
    vector<edge> adj;
    int num, low, parent; // DFS numbering, lowpoint and the parent
    bool art; // this node is an articulation point
};

node g[MAXN];
int n, m;
int T; // DFS numbering
stack<edge> edgeStack;

// Store the results, O(V+E) memory
vector<vector<edge>> components;
vector<edge> bridges;
vector<int> articulationPoints;

void tarjan(int root, int curr)
{
    // For each tree edge A-B we check:
    // (1) low(B)>A => A-B is a bridge
    // (2) low(B)>=A => A is an articulation point
    // (3) low(B)>=A => B is the root of a biconnected component
    int treeChildren = 0;
    g[curr].low = g[curr].num = T++;
    for(edge &e : g[curr].adj)
    {
        // Skip the parent edge and forward edges
        int nxt = e.b;
        if(nxt == g[curr].parent || g[nxt].num > g[curr].num)
        {
            continue;
        }
        edgeStack.push(e);
        if(g[nxt].num == 0)
        {
            // Tree edge
            g[nxt].parent = curr;
            treeChildren++;
            tarjan(root, nxt);
            g[curr].low = min(g[curr].low, g[nxt].low);
            if(g[nxt].low > g[curr].num)
            {
                // New bridge
                bridges.push_back(e);
            }
            if(g[nxt].low >= g[curr].num)
            {
                // Possibly new articulation point
                // If curr is a root it needs to have more than 1 tree child
                if(!g[curr].art && (curr != root || treeChildren > 1))
                {
                    g[curr].art = true; 
                    articulationPoints.push_back(curr);
                }
                // New biconnected component
                vector<edge> component;
                edge last;
                do
                {
                    last = edgeStack.top();
                    component.push_back(last);
                    edgeStack.pop();
                }
                while(last.a != curr);
                components.push_back(component);
            }
        }
        else 
        {
            // Back edge
            g[curr].low = min(g[curr].low, g[nxt].num);
        }
    }
}

void printComponents()
{
    printf("\nComponents:");
    for(auto &component : components)
    {
        printf("\n");
        for(edge &e : component)
        {
            printf("%d-%d ", e.a, e.b);
        }
    }
    printf("\nTotal number of biconnected components: %d.\n", components.size());
}

void printArticulationPoints()
{
    printf("\nArticulation Points:\n");
    for(int point : articulationPoints)
    {
        printf("%d ", point);
    }
    printf("\nTotal number of articulation points: %d.\n", articulationPoints.size());
}

void printBridges()
{
    printf("\nBridges:\n");
    for(edge &e : bridges)
    {
        printf("%d-%d ", e.a, e.b);
    }
    printf("\nTotal number of bridges: %d.\n", bridges.size());
}

// Testing
// Test problem: http://www.spoj.com/problems/SUBMERGE/
int main()
{
    while(1)
    {
        scanf("%d %d", &n, &m);
        if(n == 0 && m == 0)
        {
            return 0;
        }
        // Reset
        components.clear();
        bridges.clear();
        articulationPoints.clear();
        for(int i = 1; i <= n; i++)
        {
            g[i].adj.clear();
            g[i].num = g[i].low = g[i].parent = 0;
            g[i].art = false;
        }
        for(int i = 0; i < m; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            g[u].adj.push_back({u, v});
            g[v].adj.push_back({v, u}); // undirected
        }
        T = 1; // DFS numbering
        for(int i = 1; i <= n; i++)
        {
            if(g[i].num == 0)
            {
                tarjan(i, i);
            }
        }
        // printComponents();
        // printArticulationPoints();
        // printBridges();
        printf("%d\n", articulationPoints.size());
    }
    return 0;
}

/*
Test case from http://en.wikipedia.org/wiki/Biconnected_component
14 16
1 2 
1 3
2 4
3 4
4 5
5 6
6 7
7 8
7 9
9 10
9 11
11 12
12 13
12 14
13 14
13 7
*/