// RandomUsername (Nikola Jovanovic)
// Bit Manipulation

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
#define MAXN 105
#define MOD 1000000007

using namespace std;

// Practice problems for Bitmask DP:
// http://www.spoj.com/problems/HIST2/
// http://www.spoj.com/problems/LINEUP/
int main()
{
    // Usual Bitmask DP scenario:
    // We're using bitmasks to represent subsets of an n-item set
    // Usually we clear a bit in a bitmask and then use a recurrence relation

    // Set size
    int n = 10;
    // The total number of possible subsets
    int MASKS = (1 << n);

    // Traversing all states
    for(int MASK = 0; MASK < MASKS; MASK++)
    {
        // Traversing all bits
        for(int bit = 0; bit <= n-1; bit++)
        {
            // Standard bit manipulation functions

            // Set/clear/flip this bit
            int SET = MASK | (1 << bit);
            int CLEAR = MASK & ~(1 << bit);
            int FLIP = MASK ^ (1 << bit);

            // Check if this bit is set
            int TEST = (MASK & (1 << bit)) != 0;

            // Count trailing/leading zeros
            int TRAIL = __builtin_ctz(MASK);
            int LEAD = __builtin_clz(MASK);

            // Count the number of set bits
            int CNTSET = __builtin_popcount(MASK);
        }
    }
    return 0;
}
