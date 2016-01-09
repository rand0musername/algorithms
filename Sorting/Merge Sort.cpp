// RandomUsername (Nikola Jovanovic)
// Merge Sort
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
// Helper array
int tmp[MAXN];

void mergeSort(int l, int r)
{
    if(l == r)
        return;

    mergeSort(l, mid);
    mergeSort(mid+1, r);

    // Merge
    int i = l;
    int j = mid+1;
    for(int it = l; it <= r; it++)
    {
        if(j > r)
            tmp[it] = a[i++];
        else if(i > mid)
            tmp[it] = a[j++];
        else if(a[i] <= a[j])
            tmp[it] = a[i++];
        else
            tmp[it] = a[j++];
    }
    for(int it = l; it <= r; it++)
    {
        a[it] = tmp[it];
    }

}

// Testing
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    mergeSort(1, n);
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
