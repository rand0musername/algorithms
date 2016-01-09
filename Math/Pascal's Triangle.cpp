// RandomUsername (Nikola Jovanovic)
// Pascal's Triangle
// Table of binomial coefficients up to C(N, K): O( N*K )

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
#define MOD 1000000007

using namespace std;

lld bc[MAXN][MAXN];

// C(n, k) = C(n-1, k-1) + C(n-1, k)
void pascal(lld n, lld k)
{
    // C(n, k) for k > n = 0
    for(int i = 0; i <= n; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            if(j == 0)
                bc[i][j] = 1;
            else
                bc[i][j] = bc[i-1][j-1] + bc[i-1][j];
        }
    }
}

// Testing
int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    pascal(n, k);
    printf("Pascal's Triangle:\n");
    for(int i = 0; i <= n; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            printf("%d ", bc[i][j]);
        }
        printf("\n");
    }
    return 0;
}
