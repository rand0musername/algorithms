// RandomUsername (Nikola Jovanovic)
// Contest Name
// Problem Name

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

int n, m, t, ret;
int a[MAXN];

int foo(int bar)
{
    int ret = 1;
    return ret;
}

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &n, &m);
        ff(i, 1, n)
        {
            scanf("%d", &a[i]);
            ret += foo(a[i]);
        }
        printf("%d\n", ret);
    }
    return 0;
}
