// RandomUsername (Nikola Jovanovic)
// Binary Indexed Tree 2D
// inc: O( logNlogM )
// get: O( logNlogM) )
// getRect: O( logNlogM )
// N - matrix height, M - matrix width

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
#define MAXN 1005

using namespace std;

// Matrix and its size, BIT
int a[MAXN][MAXN], n, m, bit[MAXN][MAXN];

// a[i] += inc
void inc(int i, int j, int inc)
{
    while(i <= n)
    {
        int j1 = j;
        while(j1 <= m)
        {
            bit[i][j1] += inc;
            j1 += (j1 & -j1);
        }
        i += (i & -i);
    }
}

// a[1][1]+..+a[i][j]
int get(int i, int j)
{
    int ret = 0;
    while(i >= 1)
    {
        int j1 = j;
        while(j1 >= 1)
        {
            ret += bit[i][j1];
            j1 -= (j1 & -j1);
        }
        i -= (i & -i);
    }
    return ret;
}

// a[i1][j1]+..+a[i2][j2]
int getRect(int i1, int j1, int i2, int j2) // Inclusion–exclusion principle
{
    return get(i2, j2) - get(i1 - 1, j2) - get(i2, j1 - 1) + get(i1 - 1, j1 - 1);
}

// Testing
// Test problem: http://www.codechef.com/problems/MATSUM/
int main()
{
    int q, i1, j1, i2, j2, v, l, r, kom;
    scanf("%d %d %d", &n, &m, &q);
    while(q--)
    {
        scanf("%d", &kom);
        if(kom == 1) // increment by inc
        {
            scanf("%d %d %d", &i1, &j1, &v);
            inc(i1, j1, v);
        }
        else if(kom == 2) //getRect (i1,j1) - (i2,j2)
        {
            scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
            printf("%d\n", getRect(i1, j1, i2, j2));
        }
    }
    return 0;
}
