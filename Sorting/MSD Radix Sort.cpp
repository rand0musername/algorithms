// RandomUsername (Nikola Jovanovic)
// MSD Radix Sort
// Sorting an array: O( N * W )
// N - array size, W - word size

#include <bits/stdc++.h>
#include <unistd.h>
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
void countingSort(int l, int r, int pos)
{
    // Reset cnt array
    int cnt[10];
    for(int i = 0; i <= 9; i++)
    {
        cnt[i] = 0;
    }
    // Count every element
    for(int i = l; i <= r; i++)
    {
        cnt[digitAt(a[i], pos)]++;
    }
    // Calculate indices
    for(int i = 1; i <= 9; i++)
    {
        cnt[i] += cnt[i-1];
    }
    // Place the elements in a temporary array
    for(int i = r; i >= l; i--)
    {
        int idx = (l - 1) + cnt[digitAt(a[i], pos)]--;
        tmp[idx] = a[i];
    }
    // Put the elements back
    for(int i = l; i <= r; i++)
    {
        a[i] = tmp[i];
    }    
    // Recurse
    if(pos == 0)
    {
        return;
    }
    int last = l;
    for(int i = l+1; i <= r; i++)
    {
        if(digitAt(a[i], pos) > digitAt(a[i-1], pos))
        {
            countingSort(last, i - 1, pos - 1);
            last = i;
        }
    }
    countingSort(last, r, pos - 1);
}

void msdRadixSort()
{
    countingSort(1, n, 9);
}

// Testing
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    msdRadixSort();
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
