// RandomUsername (Nikola Jovanovic)
// LSD Radix Sort
// Sorting an array: O( N * W )
// N - array size, W - word size

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
#define MAXNUM 1000005
#define MOD 1000000007

using namespace std;

// The array we're sorting and its size
int a[MAXN];
int tmp[MAXN];
int n;

// Extract digit at position pos
int digitAt(int n, int pos)
{
    return (n / lrint(pow(10, pos))) % 10;
}

// Stable version
bool countingSort(int pos)
{
    // Reset cnt array
    int cnt[10];
    for(int i = 0; i <= 9; i++)
    {
        cnt[i] = 0;
    }
    // Count every element
    for(int i = 1; i <= n; i++)
    {
        cnt[digitAt(a[i], pos)]++;
    }
    // Sorted
    if(cnt[0] == n)
    {
        return true;
    }
    // Calculate indices
    for(int i = 1; i <= 9; i++)
    {
        cnt[i] += cnt[i-1];
    }
    // Place the elements in a temporary array
    for(int i = n; i >= 1; i--)
    {
        int idx = cnt[digitAt(a[i], pos)]--;
        tmp[idx] = a[i];
    }
    // Put the elements back
    for(int i = 1; i <= n; i++)
    {
        a[i] = tmp[i];
    }
    // Not sorted
    return false;
}

void lsdRadixSort()
{
    for(int pos = 0; pos <= 9; pos++)
    {
        if(countingSort(pos))
        {
            return;
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
    lsdRadixSort();
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
