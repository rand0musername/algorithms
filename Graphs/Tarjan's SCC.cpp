// RandomUsername (Nikola Jovanovic)
// Tarjan's algorithm for finding strongly connected
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
    vector<int> adj;
    int num, low; // DFS numbering, lowpoint
    bool onStack; // visited vertex without a component
    int comp; // index of the SCC this node belongs to
};

node g[MAXN];
int n, m;
int T; // DFS numbering
stack<int> s; // vertices without a component

// Store the results, O(V) memory
vector<vector<int>> components;

void tarjan(int curr)
{
    // For each node A we check:
    // low(A)==A => A is a head of a strongly connected component
    int treeChildren = 0;
    g[curr].low = g[curr].num = T++;
    s.push(curr);
    g[curr].onStack = true;
    for(int nxt : g[curr].adj)
    {
        if(g[nxt].num == 0)
        {
            // Tree edge
            tarjan(nxt);
            g[curr].low = min(g[curr].low, g[nxt].low);
        }
        else if(g[nxt].onStack)
        {
            // Relevant back/cross edge
            g[curr].low = min(g[curr].low, g[nxt].num);
        }
    }
    if(g[curr].low == g[curr].num)
    {
        // New strongly connected component
        vector<int> component;
        int last = 0;
        do
        {
            last = s.top();
            component.push_back(last);
            g[last].comp = components.size() + 1; // Counting SCCs from 1
            s.pop();
        }
        while(last != curr);
        components.push_back(component);
    }
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
            g[i].num = g[i].low = g[i].comp = 0;
            g[i].onStack = false;
            sinkComponent[i] = true;
        }
        for(int i = 0; i < m; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            g[u].adj.push_back(v);
        }
        T = 1; // DFS numbering
        for(int i = 1; i <= n; i++)
        {
            if(g[i].num == 0)
            {
                tarjan(i);
            }
        }
        // printComponents();
        // We are looking for all SCCs with 0 outgoing
        // edges in the component graph
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