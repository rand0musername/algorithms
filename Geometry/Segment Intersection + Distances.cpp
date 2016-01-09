// RandomUsername (Nikola Jovanovic)
// Segment Intersection + Distances

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

// Distance between two points
double dist(point a, point b)
{
	return sqrt( (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) );
}

// Cross product |ab| x |bc|
lld cross(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
    // >0 - left turn
    // <0 - right turn
    // =0 - collinear
}

// Distance from point c to line ab
double pointdis(point a, point b, point c)
{
	return cross(a,b,c) / dist(a,b);
}

// Helper function, checks if a and b are on the same side of cd
lld side(point a, point b, point c, point d)
{
    return cross(c, d, a) * cross(c, d, b);
    // >0 = same turn = same side of cd
    // <0 = diff turn = diff side of cd
    // =0 = a or b on cd
}

// Check if line segments |ab| and |cd| intersect
bool intersect(point a, point b, point c, point d)
{
    // Lines intersect with segments + the projections intersect
    if( side(a, b, c, d) <= 0 && side(c, d, a, b) <= 0 &&
    min(a.x, b.x) <= max(c.x, d.x) &&
    min(c.x, d.x) <= max(a.x, b.x) &&
    min(a.y, b.y) <= max(c.y, d.y) &&
    min(c.y, d.y) <= max(a.y, b.y) )
        return true;
    else
        return false;
}

// Testing
int main()
{
    point a, b, c, d;
    scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y);
    if(intersect(a, b, c, d))
        printf("The line segments do intersect.");
    else
        printf("The line segments don't intersect.");
    return 0;
}
