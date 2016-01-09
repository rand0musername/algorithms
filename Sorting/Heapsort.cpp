// RandomUsername (Nikola Jovanovic)
// Heapsort
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
// The size of our maxHeap
int heapSz;

void heapify(int i)
{
    int swp;
    while(i <= heapSz)
    {
        swp = i;
        if(2*i <= heapSz && a[2*i] > a[swp])
            swp = 2*i;
        if(2*i + 1 <= heapSz && a[2*i+1] > a[swp])
            swp = 2*i + 1;
        if(swp == i)
            return;
        else
            swap(a[i], a[swp]), i = swp;
    }
}

void pop()
{
    swap(a[1], a[heapSz--]);
    int i = 1, swp;
    while(i <= heapSz)
    {
        swp = i;
        if(2*i <= heapSz && a[2*i] > a[swp])
            swp = 2*i;
        if(2*i + 1 <= heapSz && a[2*i+1] > a[swp])
            swp = 2*i + 1;
        if(swp == i)
            return;
        else
            swap(a[i], a[swp]), i = swp;
    }
}

void heapsort()
{
    // heapify - bottom up
    heapSz = n;
    for(int i = n; i >= 1; i--)
    {
        // sink this node
        heapify(i);
    }
    // extractMax
    for(int i = 1; i <= n; i++)
    {
        pop();
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
    heapsort();
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
