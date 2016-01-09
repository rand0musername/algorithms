// RandomUsername (Nikola Jovanovic)
// Trie
// Initialize: O(N)
// Insert a string: O(N)
// Find a string: O(N)
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
#define MAXN 1000005
#define MAXLOGN 20

using namespace std;


struct trieNode
{
    // Children
    unordered_map<char, trieNode*> adj;
    // A string ends here
    bool leaf;
    // Constructor
    trieNode()
    {
        leaf = false;
    }
};

// Root node
trieNode* root;

void init()
{
    root = new trieNode();
}

// Add char s[idx] as a child of the curr node
void insertStr(trieNode* curr, char* s, int idx, int len)
{
    // End of the string
    if(idx == len)
    {
        curr -> leaf = true;
        return;
    }

    // Create a missing child
    if(curr -> adj[ s[idx] ] == NULL)
        curr -> adj[ s[idx] ] = new trieNode();

    // Recurse
    insertStr(curr -> adj[ s[idx] ], s, idx+1, len);
}

// Does char s[idx] exist as a child of the curr node
bool findStr(trieNode* curr, char* s, int idx, int len)
{
    // End of the string
    if(idx == len)
    {
        return (curr -> leaf);
    }

    // If there's no child, there's no string
    if(curr -> adj[ s[idx] ] == NULL)
        return false;

    // Recurse
    return findStr(curr -> adj[ s[idx] ], s, idx+1, len);
}

// Testing
// Test problem: http://www.spoj.com/problems/PHONELST/
int main()
{
    int q, kom;
    char s[100];
    scanf("%d", &q);

    init();
    while(q--)
    {
        scanf("%d %s", &kom, s);
        if(kom == 1)
        {
            insertStr(root, s, 0, strlen(s));
        }
        else if(kom == 2)
        {
            if( findStr(root, s, 0, strlen(s)) )
                printf("Found!\n");
            else
                printf("Not found!\n");
        }
    }
    return 0;
}
