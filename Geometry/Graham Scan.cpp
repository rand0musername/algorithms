// RandomUsername (Nikola Jovanovic)
// Graham Scan
// Convex hull: O( NlogN )
// N - number of points

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
#define MOD 1000000007

using namespace std;

// PI
const double PI = atan(1) * 4;

// A structure that represents a point
struct point
{
    // Coordinates, input indes
    double x, y;
    int idx;
    // The angle this point and the starting point make with the x-axis
    double ang;
    // Distance^2 from the starting point, for dealing with angle ties
    double qdist;
    // Compare two points by angle and distance
    const bool operator < (const point b)
    const
    {
       if(ang == b.ang)
        return qdist < b.qdist;
       return ang < b.ang;
    }
};

// The number of points, the array of points, the convex hull
int n;
point a[MAXN];
vector<point> hull;

// The starting point
point p;

// Cross product
int cross(point p1, point p2, point p3)
{
    return (p2.x - p1.x) * (p3.y - p2.y) - (p2.y - p1.y) * (p3.x - p2.x);
    // <0 - right turn
    // >0 - left turn
    // =0 - collinear
}

void GrahamScan()
{
    // Clear the hull vector
    hull.clear();

    // Find the starting point
    p = a[1];
    for(int i = 2; i <= n; i++)
    {
        if( a[i].y < p.y || (a[i].y == p.y && a[i].x < p.x) )
            p = a[i];
    }

    // Calculate angles and sort
    for(int i=1; i<=n; i++)
    {
        // atan2: [-PI,PI]
        // p.y = miny => [0,PI]
        a[i].ang = atan2(a[i].y - p.y, a[i].x - p.x);
        a[i].qdist = (a[i].y - p.y) * (a[i].y - p.y) + (a[i].x - p.x) * (a[i].x - p.x);
    }
    sort(a+1, a+n+1);

    // Start the scan

    // Initially, first two points are in the hull
    hull.push_back( a[1] );
    hull.push_back( a[2] );

    //Scan all the points
    for(int i=3; i<=n; i++)
    {
        /*
            We observe the turn last two points make with the point we're trying to introduce
            While it's a right turn we discard the last point from the hull
            We keep discarding until we can safely add a[i]
            < - all points on the hull
            <= - the least number of points on the hull (no 3 collinear)
        */

        while( cross( hull[hull.size() - 2], hull[hull.size() - 1], a[i] ) < 0 )
            hull.pop_back();
        hull.push_back(a[i]);
    }
}

// Testing
// Test problem: http://www.spoj.com/problems/BSHEEP/
int main()
{
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
    {
        scanf("%lf %lf", &a[i].x, &a[i].y);
        a[i].idx = i;
    }
    GrahamScan();

    printf("Convex hull:\n");
    for(int i = 0; i < hull.size(); i++)
      printf("%d(%.2f, %.2f)\n", hull[i].idx, hull[i].x, hull[i].y);

    return 0;
}
