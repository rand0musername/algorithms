// RandomUsername (Nikola Jovanovic)
// Pick's Theorem + Polygon Area

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
#define MAXN 105
#define MOD 1000000007

using namespace std;

// Point structure
struct point
{
    // Coordinates
    double x, y;

    // Empty constructor
    point()
    {

    }

    // Constructor
    point(double x, double y)
    {
        this -> x = x;
        this -> y = y;
    }
};

// Area of the polygon
// The points are assumed to be ordered counter-clockwise
double polyArea(point* p, int n)
{
	double ret = 0;
	for(int i = 0; i <= n-1; i++)
    {
        // Summing the signed projections
        ret += ( p[i].x + p[ (i+1)%n ].x ) * ( p[ (i+1)%n ].y - p[i].y );
    }
    return ret / 2;
}

// Number of integer points on the edge of the polygon
int polyEdge(point* p, int n)
{
    int ret = 0;
    for(int i = 0; i <= n-1; i++)
    {
        ret += __gcd( int(abs( p[i].x - p[ (i+1)%n ].x )), int(abs( p[i].y - p[ (i+1)%n ].y )) );
    }
    return ret;
}

// Integer points inside the polygon (Pick's theorem)
// https://upload.wikimedia.org/wikipedia/commons/f/f1/Pick-theorem.png
int polyInside(point* p, int n)
{
    return round( polyArea(p, n) + 1 - polyEdge(p, n) / 2.0 );
}

// Testing
int main()
{
    int n;
    point p[MAXN];
    // Counterclockwise
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%lf %lf", &p[i].x, &p[i].y);
    }
    printf("Area: %.2f\n", polyArea(p, n));
    printf("Integer points on the boundary: %d\n", polyEdge(p, n));
    printf("Integer points inside: %d\n", polyInside(p, n));
    return 0;
}
