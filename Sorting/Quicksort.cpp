// RandomUsername (Nikola Jovanovic)
// Quicksort
// Sorting an array: O( NlogN )
// N - array size

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

// The array we're sorting and its size
int a[MAXN];
int n;

void quicksort(int l, int r)
{
    if(l >= r)
        return;

    int smallIdx = l-1;
    for(int i = l; i < r; i++)
    {
        // Pivot: a[r]
        if(a[i] < a[r])
        {
            swap(a[++smallIdx], a[i]);
        }
    }
    // Put the pivot in the middle
    swap(a[r], a[smallIdx + 1]);
    quicksort(l, smallIdx);
    quicksort(smallIdx + 2, r);
}

// Testing
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    quicksort(1, n);
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
