// RandomUsername (Nikola Jovanovic)
// Rabin-Karp
// String matching: O( N + M ) (if the hash creates no collisions)
// N - word length, M - text length

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

using namespace std;

// Text and text length, word and word length
// Searching for word in text
char t[MAXLEN];
lld tl;
char w[MAXLEN];
lld wl;
// Matches
vector<int> matches;

/*
    Rolling hash: h(s) = product(s[i] * P^i) % MOD
    Changing i-th char to ch: h(s) - s[i] * P^i + ch * P^i
    Appending char ch to the end: h(s) + ch * P^length(s)
    Appending char ch to the beginning: h(s) * P + ch * P^0
    Hashing s[i..j]: ( h(s[0..j]) - h(s[0..i-1]) ) / P^i (modular inverse)

    #include <unordered_set>
*/

const lld P = 2;
const lld MOD = 1000003;

// Precalcute powers of P modulo MOD
lld powp[MAXLEN];
void initPowP()
{
    powp[0] = 1;
    for (int i = 1; i < MAXLEN; i++)
        powp[i] = (powp[i-1] * P) % MOD;
}

// Modular inverse
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
lld mulinv(lld x)
{
    return fastpow(x, MOD - 2);
}

// Rolling hash
lld rollingHash(char* s)
{
    lld H = 0;
    int len = strlen(s);
    for(int i = 0; i < len; i++)
    {
        H = (H + s[i] * powp[i]) % MOD;
    }
    return H;
}

void testMatch(lld wordHash, lld H, int idx)
{
    if(wordHash != H)
        return;
    // actual check if the hash has collisions
    /*
    for(int i = 0; i < wl; i++)
    {
        if(t[idx + i] != w[i])
            return;
    }
    */

    matches.push_back(idx);
    return;
}

// String matching
void RK()
{
    lld wordHash = rollingHash(w);
    // roll through the text keeping the hash of each substring of length wl
    lld H = 0;
    for(int i = 0; i < wl; i++)
    {
        // build the first string
        H = (H + t[i] * powp[i]) % MOD;
    }
    testMatch(wordHash, H, 0);
    for(int i = wl; i < tl; i++)
    {
        // swap and compare
        H = ( H + MOD - t[i-wl] * powp[0] ) % MOD; // delete
        H = ( H * mulinv(powp[1]) ) % MOD; // adjust
        H = ( H + t[i] * powp[wl-1] ) % MOD; // add
        testMatch(wordHash, H, i - wl + 1);
    }

}

// Testing
// Test problem: http://www.spoj.com/problems/NHAY/
int main()
{
    initPowP();
    scanf("%s", t);
    scanf("%s", w);
    tl = strlen(t);
    wl = strlen(w);
    RK();
    printf("Matches:\n");
    for(int i = 0; i < matches.size(); i++)
        printf("%d ", matches[i]);
    return 0;
}
