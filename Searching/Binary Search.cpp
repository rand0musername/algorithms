// RandomUsername (Nikola Jovanovic)
// Binary Search
// Finding an element in a sorted array: O( log(N) )
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
#define MAXN 10005
#define MOD 1000000007

using namespace std;

// Array of integers, and its size
int a[MAXN];
int n;

// Locate the number x in a[l..r]
int binarySearch(int x, int l, int r)
{
    int hi = r;
    int lo = l;
    int pivot;
    while(hi > lo)
    {
        pivot = (hi + lo) / 2;
        if(a[pivot] < x) lo = pivot + 1;
        else if(a[pivot] > x) hi = pivot - 1;
        else return pivot;
    }
    if(a[hi] == x)
        return hi;
    // x not found
    return -1;
}


// Testing
// Test problem: http://www.spoj.com/problems/BSEARCH1/
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    sort(a+1, a+n+1);

    int q, x;
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d", &x);
        printf("Element %d at index %d\n", x, binarySearch(x, 1, n));
    }
    return 0;
}
