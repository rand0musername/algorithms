// RandomUsername (Nikola Jovanovic)
// Hierholzer's Eulerian Path
// O(E)
// Path/Trail/Walk
// * Visits each edge once, Graph \ {0-degree vertices} is connected
// * start != end, 0 or 2 odd degree vertices
// Cycle/Circuit/Tour
// * Visits each edge once, Graph \ {0-degree vertices} is connected
// * start == end, no odd degree vertices

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
    unordered_set<int> free; // free edges
    bool visited;
};

// The graph
node g[MAXN];
int n, m;

// Connectivity
void DFS(int curr)
{
    g[curr].visited = true;
    int sz = g[curr].adj.size();
    for(int i = 0; i < sz; i++)
    {
        int nxt = g[curr].adj[i];
        if(!g[nxt].visited)
        {
            DFS(nxt);
        }
    }
}

// Graph \ {0-degree vertices} has to be connected
bool almostConnected()
{
    DFS(1);
    for(int i = 1; i <= n; i++)
    {
        if(!g[i].adj.empty() && !g[i].visited)
        {
            return false;
        }
    }
    return true;
}

// Hierholzer's algorithm
vector<int> hierholzer(int startNode)
{
    // Prepare free edges
    for(int i = 1; i <= n; i++)
    {
        int sz = g[i].adj.size();
        for(int j = 0; j < sz; j++)
        {
            int nxt = g[i].adj[j];
            g[i].free.insert(nxt);
        }
    }
    // Init
    stack<int> path;
    stack<int> backtrack;
    int curr = startNode;
    path.push(curr);
    // The path could be extended
    while(!path.empty())
    {
        // As long as the last node on the path
        // has unused edges we extend the path
        while(!g[curr].free.empty())
        {
            int nxt = *g[curr].free.begin();
            path.push(nxt);
            g[curr].free.erase(nxt);
            g[nxt].free.erase(curr);
            curr = nxt;
        }
        // We are stuck, we need to backtrack and
        // find a place where the path can be extended
        while(g[curr].free.empty())
        {
            backtrack.push(path.top());
            path.pop();
            if(path.empty())
            {
                break;
            }
            curr = path.top();
        }
    }
    // Return a vector
    vector<int> ret;
    while(!backtrack.empty())
    {
        ret.push_back(backtrack.top());
        backtrack.pop();
    }
    return ret;
}

// Find a Path
vector<int> getPath()
{
    int oddNode = 1;
    int oddCnt = 0;
    vector<int> ret;
    for(int i = 1; i <= n; i++)
    {
        if(g[i].adj.size() % 2 == 1)
        {
            oddCnt++;
            oddNode = i;
        }
    }
    if(oddCnt != 0 && oddCnt != 2)
    {
        // Eulerian Path doesn't exist
        return ret;
    }
    // Start from any odd node / any node if all are even
    ret = hierholzer(oddNode);
    return ret;
}

// Find a Cycle
vector<int> getCycle()
{
    vector<int> ret;
    for(int i = 1; i <= n; i++)
    {
        if(g[i].adj.size() % 2 == 1)
        {
            // Eulerian Cycle doesn't exist
            return ret;
        }
    }
    ret = hierholzer(1);
    return ret;
}

// Testing
// TP: http://pastebin.com/raw.php?i=SVH4X3hW
int main()
{
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v); 
        g[u].adj.push_back(v);
        g[v].adj.push_back(u); // undirected graph
    }
    if(!almostConnected())
    {
        printf("No Eulerian path. Graph not connected.\n");
        printf("No Eulerian cycle. Graph not connected.\n");
        return 0;
    }
    // Eulerian Path
    vector<int> path = getPath();
    if(path.empty())
    {
        printf("No Eulerian path.\n");
    }
    else
    {
        printf("Eulerian path:\n");
        for(int v : path)
        {
            printf("%d ", v);
        }
        printf("\n");
    }
    // Eulerian Cycle
    vector<int> cycle = getCycle();
    if(cycle.empty())
    {
        printf("No Eulerian cycle.\n");
    }
    else
    {
        printf("Eulerian cycle:\n");
        for(int v : cycle)
        {
            printf("%d ", v);
        }
        printf("\n");
    }
    return 0;
}