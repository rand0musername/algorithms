// RandomUsername (Nikola Jovanovic)
// Ternary Search
// Finding the maximum/minimum of a unimodal function: O( log(N) )
// N - range / precision

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
#define MAXN 10005
#define MOD 1000000007

using namespace std;

// Precision
const double EPS = 1e-9;

// A convex function
double f(double x)
{
    return (x - 1) * (x - 1) + 13.37;
}

double ternarySearch(double l, double r)
{
    // We have achieved the needed precision
    if(r - l < EPS)
        return (l + r) / 2.0;

    // Two random points (1/3 and 2/3 of the range)
    double m1 = (2.0 * l + r) / 3.0;
    double m2 = (l + 2.0 * r) / 3.0;

    // Convex functions: >
    // Concave functions: < (Flip the sign!)
    // If f(m1) > f(m2) m1 is on the left side so we can cut the far left part off
    if( f(m1) > f(m2) )
        return ternarySearch(m1, r);
    else
        return ternarySearch(l, m2);
}

// Testing
int main()
{
    double l, r;
    scanf("%lf %lf", &l, &r);
    double maxX = ternarySearch(l, r);
    printf("Max: (%.2f, %.2f)\n", maxX, f(maxX));
    return 0;
}
