// RandomUsername (Nikola Jovanovic)
// Counting Sort
// Sorting an array: O( N + K )
// N - array size, K - upper bound for the numbers

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
int cnt[MAXNUM];
int n;

void countingSort()
{
    // Number range: [1..MAXNUM-5]
    for(int i = 1; i <= n; i++)
        cnt[ a[i] ]++;

    int it = 1;
    for(int i = 1; i <= MAXNUM-5; i++)
    {
        while(cnt[i])
        {
            a[it++] = i;
            cnt[i]--;
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
    countingSort();
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
