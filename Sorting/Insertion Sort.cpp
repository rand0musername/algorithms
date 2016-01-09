// RandomUsername (Nikola Jovanovic)
// Insertion Sort
// Sorting an array: O( N^2 )
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

void insertionSort()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = i-1; j >= 1; j--)
        {
            if(a[j] > a[j+1])
                swap(a[j], a[j+1]);
        }
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
    insertionSort();
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
