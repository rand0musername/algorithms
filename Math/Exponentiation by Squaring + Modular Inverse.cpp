// RandomUsername (Nikola Jovanovic)
// Exponentiation by Squaring + Modular Inverse
// Exponentiation: O( log(E) )
// Finding the inverse: O( log(M) )
// E - exponent, M - modulo

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
#define MAXLEN 100005
#define MOD 1000000007

using namespace std;

// Recursive solution
lld fastpow(lld a, lld b)
{
    if(b == 0)
        return 1;

    lld m = fastpow(a, b/2);
    m = (m * m) % MOD;

    if(b & 1)
        return (m * a) % MOD;
    else
        return m;
}

// Iterative solution (less memory used)
lld fastpow_it(lld a, lld b)
{
    // a^b = a^(2^b1 + 2^b2 + ... 2^bn) [ bi - ith bit position ]
    //     = a^(2^b1) * a^(2^b2) * ... * a^(2^bn)

    lld ret = 1;
    while(b > 0)
    {
        if(b & 1)
            ret *= a;
        b >>= 1;
        a *= a;
    }
    return ret;
}

// Fermat's little theorem, works when (x, MOD) = 1
lld mulinv(lld x)
{
    return fastpow(x, MOD - 2);
}

// Testing
int main()
{
    lld a, b;
    scanf("%lld %lld", &a, &b);
    printf("%lld^%lld = %lld = %lld\n", a, b, fastpow(a, b), fastpow_it(a, b));
    printf("mulinv(%lld) = %lld\n", a, mulinv(a));
    return 0;
}
