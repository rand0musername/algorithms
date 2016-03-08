// RandomUsername (Nikola Jovanovic)
// Huffman Coding
// build_queue: O(N) if frequencies are already sorted
// build_heap: O(NlogN)
// encode/decode: O(H) on average
// [N = alphabet size, H = entropy]

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
#define MOD 1000000007

using namespace std;

// A single node in the Huffman Tree
struct TreeNode
{
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    char ch;
    bool leaf;
    double prob;
    TreeNode(char ch, double prob)
    {
        this -> left = this -> right = this -> parent = NULL;
        this -> leaf = true;
        this -> ch = ch;
        this -> prob = prob;
    }
    TreeNode(TreeNode* left, TreeNode* right)
    {
        this -> parent = NULL;
        this -> left = left;
        this -> right = right;
        this -> leaf = false;
        this -> ch = '\0';
        this -> prob = left -> prob + right -> prob;
    }
};

// Heap ordering
struct cmp
{
    bool operator()(const TreeNode *a, TreeNode *b)
    const
    {
        return a -> prob > b -> prob;
    }
};

// Tree root
TreeNode* root;

// Table of characters' relative frequencies
map<char, double> freq;
// Mapping characters to their respective tree nodes
map<char, TreeNode*> loc;

// Average entropy, the lower bound for the average char encoding length
double H = 0.0;

// We use the sample string to calculate freqs and avg entropy
void freq_analysis(string sample)
{
    for(char &ch : sample)
    {
        freq[ch]++;
    }
    for(auto &x : freq)
    {
        freq[x.first] /= sample.size();
        H += x.second * log2(1 / x.second);
    }
}

// Sorting the chars by their freqs
bool freqCmp(pair<char, double> a, pair<char, double> b)
{
    return a.second < b.second;
}

// Building the Huffman Tree using the queue method
// O(N) but we still need O(NlogN) to sort
void build_queue()
{
    queue< TreeNode* > leaves;
    queue< TreeNode* > inner;
    // Sorting the chars by their freqs
    vector< pair<char, double> > chars;
    for(auto &x: freq)
    {
        chars.push_back(x);
    }
    sort(chars.begin(), chars.end(), freqCmp);
    // create all the leaves
    for(auto &x: chars)
    {
        loc[x.first] = new TreeNode(x.first, x.second);
        leaves.push(loc[x.first]);
    }
    // merge
    while(leaves.size() + inner.size() > 1)
    {
        cout<<leaves.size()<<" "<<inner.size()<<endl;
        TreeNode *a, *b;
        // pick a
        if( !leaves.empty() && (inner.empty() || leaves.front() -> prob < inner.front() -> prob) )
        {
            a = leaves.front();
            leaves.pop();
        }
        else
        {
            a = inner.front();
            inner.pop();
        }
        // pick b
        if( !leaves.empty() && (inner.empty() || leaves.front() -> prob < inner.front() -> prob) )
        {
            b = leaves.front();
            leaves.pop();
        }
        else
        {
            b = inner.front();
            inner.pop();
        }
        TreeNode* nw = new TreeNode(a, b);
        a -> parent = b -> parent = nw;
        inner.push(nw);
    }
    // set the root
    root = inner.front();
    return;
}

// Building the Huffman Tree using the heap method
// O(NlogN)
void build_heap()
{
    priority_queue<TreeNode*, vector<TreeNode*>, cmp> pq;
    // create all the leaves
    for(auto &x : freq)
    {
        loc[x.first] = new TreeNode(x.first, x.second);
        pq.push(loc[x.first]);
    }
    while(pq.size() > 1)
    {
        // a and b are the least probable, so we merge them
        TreeNode* a = pq.top();
        pq.pop();
        TreeNode* b = pq.top();
        pq.pop();
        TreeNode* nw = new TreeNode(a, b);
        a -> parent = b -> parent = nw;
        pq.push(nw);
    }
    // set the root
    root = pq.top();
    return;
}

// Encoding a single character
string encode_char(char ch)
{
    string ret = "";
    TreeNode* curr = loc[ch];
    if(curr == NULL)
    {
        throw string("Invalid character ") + ch;
    }
    while(curr != root)
    {
        if(curr == curr -> parent -> left)
        {
            ret += '0';
        }
        else
        {
            ret += '1';
        }
        curr = curr -> parent;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

// Encoding a string
string encode(string s)
{
    string ret = "";
    for(char &ch : s)
    {
        try
        {
            ret += encode_char(ch);
        }
        catch(const string& ex)
        {
            throw;
        }
    }
    return ret;
}

// Decoding a string
string decode(string s)
{
    string ret = "";
    TreeNode* curr = root;
    for(char &ch : s)
    {
        // move further
        if(ch == '0')
        {
            curr = curr -> left;
        }
        else
        {
            curr = curr -> right;
        }
        // error?
        if(curr == NULL)
        {
            throw string("Not a valid message");
        }
        // end of the char
        if(curr -> leaf)
        {
            ret += curr -> ch;
            curr = root;
        }
    }
    return ret;
}

// Print all the relevant data
void print_info()
{
    double avg_enc_len = 0.0;
    for(auto &x : freq)
    {
        printf("freq('%c') = %7.4f\t", x.first, x.second);
        printf("H('%c') = %7.4f\t", x.first, log2(1 / x.second));
        try
        {
            string code = encode_char(x.first);
            printf("code('%c') = %s\n", x.first, code.c_str());
            avg_enc_len += x.second * code.size();
        }
        catch(const string &ex)
        {
            printf("Couldn't encode a valid char, this shouldn't happen.\n");
            return;
        }
    }
    printf("Average entropy: %7.4f\n", H);
    printf("Expected average encoding length: %7.4f\n", avg_enc_len);
}

/*
    this is a huffman tree
    HEAP
    ENC huffman
    DEC 10000010010
    LAST
    FINISH

    cdbbbbbbaaaa
    HEAP
    FINISH
*/

// Testing
int main()
{
    string s;
    string cmd;
    // Input the sample string
    getline(cin, s);
    freq_analysis(s);
    // Choose the building method
    cin >> cmd;
    if(cmd[0] == 'Q')
    {
        build_queue();
    }
    else if(cmd[0] == 'H')
    {
        build_heap();
    }
    else
    {
        return 0;
    }
    print_info();
    // Encode and decode
    string lastEncoded;
    while(true)
    {
        cin >> cmd;
        if(cmd[0] == 'E')
        {
            cin >> s;
            try
            {
                lastEncoded = encode(s);
                cout << lastEncoded << endl;
            }
            catch(const string &ex)
            {
                cout << "Encoding exception: "<< ex << endl;
            }
        }
        else if(cmd[0] == 'D')
        {
            cin >> s;
            try
            {
                cout << decode(s) << endl;
            }
            catch(const string &ex)
            {
                cout << "Decoding exception: " << ex << endl;
            }
        }
        else if(cmd[0] == 'L')
        {
            // decode last result
            try
            {
                cout << decode(lastEncoded) << endl;
            }
            catch(const string &ex)
            {
                cout << "Last decoding exception: " << ex << endl;
            }
        }
        else
        {
            // Finish
            return 0;
        }
    }
    return 0;
}