// RandomUsername (Nikola Jovanovic)
// Bubble Sort
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

void bubbleSort()
{
    bool sorted = false;
    while(!sorted)
    {
        sorted = true;
        for(int i = 1; i < n; i++)
        {
            if(a[i] > a[i+1])
            {
                swap(a[i], a[i+1]);
                sorted = false;
            }
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
    bubbleSort();
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
