// RandomUsername (Nikola Jovanovic)
// Knuth-Morris-Pratt (KMP)
// String matching: O( N + M )
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

/*
    Useful tutorial: http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=stringSearching
    Failure function f[i] := the length of the longest proper suffix=prefix for string w[ 0 ]..w[ i-1 ] (string of length i)
    If we align t[j] and w[i] and fail to match a character, we should try to match w[f[i]] and t[j]
    We move our word to the right skipping all the unnecessary comparations
    f[f[i]] is the second "best" prefix=suffix (best prefix=suffix of the best prefix=suffix )
*/

// Text and text length, word and word length
// Searching for word in text
char t[MAXLEN];
int tl;
char w[MAXLEN];
int wl;

// Matches will be stored here
vector<int> matches;

// Failure function
int F[MAXLEN];

// KMP
void KMP()
{
    // Computing the faliure function
    int i, j;
    // Base cases
    F[0] = F[1] = 0;
    // Computing F[i]
    for(i = 2; i <= wl; i++)
    {
        // Expanding the solution for i-1 is our best guess for F[i]
        j = F[i-1];
        while(1)
        {
            // If w[j] and w[i-1] match, we expand, F[i] is found, break
            if(w[j] == w[i-1])  { F[i] = j + 1;  break; }
            // If we failed to expand an empty string, we have to quit trying, F[i] is zero, break
            if(j == 0) { F[i] = 0;  break; }
            // Otherwise we just try expanding the next best match
            j = F[j];
        }
    }

    // Doing the actual matching
    // i - word iterator, j - text iterator
    i = j = 0;
    while(1)
    {
        // We reached the end of the text
        if(j == tl) break;

        // We are trying to match t[j] and w[i]
        if(t[j] == w[i])
        {
            // If they match, move on
            i++, j++;
            // We reached the end of the word, we found a full match!
            if(i == wl)
            {
                // The match starts at t[j-wl]
                matches.push_back(j - wl);
                // The next possible match
                i = F[i];
            }
        }
        // If they do not match, try the next possible match for t[j]
        else if(i > 0) i = F[i];
        // If i=0 failed to match there are no more possible matches for t[j], move on
        else j++;
    }
}

// Testing
// Test problem: http://www.spoj.com/problems/NHAY/
int main()
{
    scanf("%s", t);
    scanf("%s", w);
    tl = strlen(t);
    wl = strlen(w);
    KMP();
    printf("Matches:\n");
    for(int i = 0; i < matches.size(); i++)
        printf("%d ", matches[i]);
    return 0;
}
