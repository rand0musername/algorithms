// RandomUsername (Nikola Jovanovic)
// Quickselect
// Finding the k-th smallest element in an unsorted array: O( N )
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

// Locate the k-th smallest number in a[l..r]
int quickselect(int l, int r, int k)
{
    if(l == r)
        return a[l];

    // a[l..smallIdx] - smaller than pivot
    // a[smallIdx+1..r-1] - larger or equal to pivot
    // a[r] - pivot

    int smallIdx = l-1;
    for(int i = l; i < r; i++)
    {
        if(a[i] < a[r])
        {
            swap(a[++smallIdx], a[i]);
        }
    }
    // Put the pivot in the middle
    swap(a[r], a[smallIdx + 1]);
    int smallCnt = smallIdx - l + 1;
    if(smallCnt == k - 1)
        return a[smallIdx + 1]; // return pivot
    else if(smallCnt >= k)
        return quickselect(l, smallIdx, k); // search left
    else
        return quickselect(smallIdx + 2, r, k - smallCnt - 1); // search right
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

    int q, k;
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d", &k);
        if(k < 1 || k > n)
            printf("Invalid query.\n");
        else
            printf("%d. smallest element is %d\n", k, quickselect(1, n, k));
    }
    return 0;
}
