// RandomUsername (Nikola Jovanovic)
// Suffix Array + LCP Array
// Building SA: O( N * log^2(N) )
// Building LCP: O( N )
// N - string length

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

// Length of the string, global iterator
int n, it;
// The actual string, suffix array and LCP array
char s[MAXLEN];
int SA[MAXLEN], LCP[MAXLEN];
// Position of a suffix in SA (buckets used as a hint for sorting)
int buck[MAXLEN], tmp[MAXLEN];

// Used for smart sorting while building SA
bool suffcmp(int i, int j)
{
    // If they're in different buckets
    if( buck[i] != buck[j] )
        return buck[i] < buck[j];
    // If they're in the same bucket, jump it positions
    i += it, j += it;
    // Compare again
    if(i < n && j < n)
        return buck[i] < buck[j];
    else
        return i > j;
}

// Build the SA (sorted array of suffixes)
void buildSA()
{
    // Initialize SA (we're not storing full suffixes, only corresponding indices)
    for(int i = 0; i <= n-1; i++)
    {
        SA[i] = i;
        // Initial sorting hint is the first char
        buck[i] = s[i];
    }
    // Improve with exponential increments
    for(it = 1; it <= 2*n; it *= 2)
    {
        // Sort using current buckets
        sort(SA, SA + n, suffcmp);
        // Update the buckets, prepare for the next iteration
        for(int i = 0; i <= n - 2; i++)
        {
            tmp[i+1] = tmp[i];
            if( suffcmp(SA[i], SA[i+1]) )
                tmp[i+1]++;
        }
        // Copy the buckets where they belong
        for(int i = 0; i <= n - 1; i++)
        {
            buck[ SA[i] ] = tmp[i];
        }
        // If they are sorted (we have n buckets), break
        if( tmp[n - 1] == n - 1)
            break;
    }
}

// Build the LCP array
// LCP[i] := Longest_common_prefix(SA[i], SA[i+1])
void buildLCP()
{
    // Current longest prefix
    int currPaired = 0;
    // Main loop (looping by original order: banana -> anana -> ... -> na -> a)
    for(int i = 0; i <= n - 1; i++)
    {
        // s[len] doesn't exist, so skip this one (currPaired is always 0 here)
        if(buck[i] == n - 1)
            continue;
        // Finding i's successor in SA
        int j = SA[ buck[i] + 1];
        // Expand currPaired
        while( s[i + currPaired] == s[j + currPaired] )
            currPaired++;
        // Write it down
        LCP[ buck[i] ] = currPaired;
        // Decrease currPaired by one to prepare for the next iteration
        // (LCP(i, succ(i)) = currPaired => LCP(i+1, succ(i+1)) >= currPaired - 1)
        if( currPaired > 0 )
            currPaired--;
    }
}

// Testing
// Test problem: http://www.spoj.com/problems/DISUBSTR/
int main()
{
    scanf("%s", s);
    n = strlen(s);

    buildSA();
    printf("Suffix Array:\n");
    for(int i = 0; i <= n-1; i++)
        printf("SA[%2d] = %2d (%s)\n", i, SA[i], s + SA[i]);

    buildLCP();
    printf("LCP Array:\n");
    for(int i = 0; i <= n-2; i++)
        printf("LCP[%2d] = %2d\n", i, LCP[i]);

    return 0;
}
