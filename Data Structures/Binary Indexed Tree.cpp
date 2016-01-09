// RandomUsername (Nikola Jovanovic)
// Binary Indexed Tree
// inc: O( logN )
// get: O( logN )
// getRange: O( logN )
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

// Array and its length, BIT
int a[MAXN], n, bit[MAXN];

// a[i] += inc
void inc(int i, int inc)
{
    while(i <= n)
    {
        bit[i] += inc;
        i += (i & -i);
    }
}

// a[1]+..+a[i]
int get(int i)
{
    int ret = 0;
    while(i >= 1)
    {
        ret += bit[i];
        i -= (i & -i);
    }
    return ret;
}

// a[l]+..+a[r]
int getRange(int l, int r)
{
    return get(r) - get(l-1);
}

// Testing
// Test problem: http://www.spoj.com/problems/INVCNT/
int main()
{
    int q, l, r, kom, idx, v;
    scanf("%d %d", &n, &q);
    while(q--)
    {
        scanf("%d",&kom);
        if(kom == 1) // increment by inc
        {
            scanf("%d %d", &idx, &v);
            inc(idx, v);
        }
        else if(kom == 2) // sum [l,r]
        {
            scanf("%d %d", &l, &r);
            printf("%d\n", getRange(l, r));
        }
    }
    return 0;
}
