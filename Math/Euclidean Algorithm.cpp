// RandomUsername (Nikola Jovanovic)
// Euclidean Algorithm
// GCD: O( log(N) )
// N - larger number

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
#define MAXLEN 100005

using namespace std;

// Greatest common divisor of a and b
int GCD(int a, int b)
{
    return b == 0 ? a : GCD(b, a % b);
}

// Testing
int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf("GCD(%d, %d) = %d\n", a, b, GCD(a, b));
    return 0;
}
