// RandomUsername (Nikola Jovanovic)
// Sparse Table
// init: O(NlogN)
// get: O(1)
// N - array size
// Common application: LCA (storing 2^n-th parent)

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
#define MAXN 1000005
#define MAXLOGN 20

using namespace std;

// Original array and its size
int a[MAXN], n;
// RMaxQ Sparse Table: st[i][deg] = max[a, a + 2^b)
int st[MAXN][MAXLOGN];
// pow2[i] = largest power of two less or equal to i
int pow2[MAXN];

void initPow2()
{
    pow2[1] = 0;
    for(int i = 2; i < MAXN; i++)
    {
        pow2[i] = pow2[i/2] + 1;
    }
}

void init()
{
    // Base case
    for(int i = 1; i <= n; i++)
        st[i][0] = a[i];

    // DP
    for(int deg = 1; (1 << deg) <= n; deg++)
    {
        for(int i = 1; i <= n; i++)
        {
            st[i][deg] = st[i][deg-1];
            int leap = (1 << (deg-1));
            if(i + leap <= n)
                st[i][deg] = max(st[i][deg-1], st[i + leap][deg-1]);
        }
    }
}

int get(int a, int b)
{
    // max on [a, b]
    int bestPow = pow2[b - a + 1];
    // first bestPow and last bestPow numbers in [a, b] have to overlap
    return max( st[a][bestPow], st[b + 1 - (1 << bestPow)][bestPow] );
}

// Testing
// Test problem: http://www.spoj.com/problems/ARRAYSUB/
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    initPow2();
    init();

    int q, l, r;
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d %d", &l, &r);
        printf("Max on [%d,%d] = %d\n", l, r, get(l, r));
    }
    return 0;
}
