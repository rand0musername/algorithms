// RandomUsername (Nikola Jovanovic)
// Sieve of Eratosthenes
// Finding all prime numbers: O( N )
// N - limit

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
#define MAXN 100005
#define MOD 1000000007

using namespace std;

// comp[i] -> the number is composite
bool comp[MAXN];
bool seg_comp[MAXN];

// Regular sieve for numbers [1..n]
void sieve(int n)
{
    for(int i = 1; i <= n; i++)
        comp[i] = false;
    comp[1] = true;
    for(int i = 2; i <= n; i++)
    {
        if(!comp[i])
        {
            for(int j = i*i; j <= n; j += i)
            {
                comp[j] = true;
            }
        }
    }
}

// Segmented sieve for numbers [a..b]
void seg_sieve(int a, int b)
{
    // With a [1..sqrt(b)] sieve we can find all primes in [a..b] in O(n) time
    int n = sqrt(b);
    sieve(n);
    // [a..b] -> [0..b-a]
    for(int i = 0; i <= b - a; i++)
        seg_comp[i] = false;
    if(a == 1)
        seg_comp[0] = true;
    for(int i = 2; i <= n; i++)
    {
        if(!comp[i])
        {
            int first_in = ( (a + i - 1) / i ) * i;
            if(first_in == i)
                first_in += i;
            for(int j = first_in; j <= b; j += i)
            {
                seg_comp[j - a] = true;
            }
        }
    }
}

// Testing
int main()
{
    int n;
    scanf("%d", &n);
    sieve(n);
    printf("Primes up to %d:\n", n);
    for(int i = 1; i <= n; i++)
        if(!comp[i])
            printf("%d ", i);
    printf("\n");

    int a, b;
    scanf("%d %d", &a, &b);
    seg_sieve(a, b);
    printf("Primes in [%d, %d]:\n", a, b);
    for(int i = a; i <= b; i++)
        if(!seg_comp[i - a])
            printf("%d ", i);
    printf("\n");

    return 0;
}
