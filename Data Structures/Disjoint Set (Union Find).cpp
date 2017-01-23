// RandomUsername (Nikola Jovanovic)
// Disjoint Set (Union Find)
// init: O( N )
// root: O( alpha(N) ) - amortized constant
// connect: O( alpha(N) ) - amortized constant
// N - array length

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

// Single node
struct node
{
    // Rank and parent
    int rnk, p;
};

// Disjoint Set of nodes and its size
node uf[MAXN];
int n;

// Build the structure
void init()
{
    for(int i = 1; i <= n; i++)
    {
        // Every vertex is a head of its own component and all ranks are zero
        uf[i].p = i;
        uf[i].rnk = 0;
    }
}

// Find the root of a node
int root(int x)
{
    // Path compression
    if( uf[x].p != x )
        uf[x].p = root( uf[x].p );
    return uf[x].p;
}

// Connect two nodes - returns true if connected, false if already connected
bool connect(int x, int y)
{
    int xroot = root(x);
    int yroot = root(y);
    if(xroot == yroot)
        return false;

    // Union by rank
    if( uf[xroot].rnk < uf[yroot].rnk )
        uf[xroot].p = yroot;
    else if( uf[yroot].rnk < uf[xroot].rnk )
        uf[yroot].p = xroot;
    else
        uf[yroot].p = xroot, uf[xroot].rnk++;
    return true;
}

// Testing
// Test problem: http://www.spoj.com/problems/PT07Y/
int main()
{
    int m, x, y;
    scanf("%d %d", &n, &m);
    int components = n;
    init();

    for(int i = 1; i <= m; i++)
    {
        scanf("%d %d", &x, &y);
        if( connect(x, y) )
            components--;
    }

    printf("The graph has %d components", components);
    return  0;
}
