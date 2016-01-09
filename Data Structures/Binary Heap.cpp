// RandomUsername (Nikola Jovanovic)
// Binary Heap
// init: O( 1 )
// push: O( logN )
// top: O( 1 )
// pop: O( logN )
// hSize/hEmpty: O( 1 )
// N - heap size

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
#define MAXN 1005

using namespace std;

// Maxheap
struct heap
{
    int h[MAXN];
    int heapSz;

    void init()
    {
        heapSz = 0;
    }

    void push(int x)
    {
        h[++heapSz] = x;
        int i = heapSz;
        while(i > 1)
        {
            if(h[i/2] < h[i])
                swap(h[i], h[i/2]), i /= 2;
            else
                return;
        }
    }

    int top()
    {
         if(hEmpty())
            return -1;
        return h[1];
    }

    void pop()
    {
        if(hEmpty())
            return;

        swap(h[1], h[heapSz--]);
        int i = 1, swp;
        while(i <= heapSz)
        {
            swp = i;
            if(2*i <= heapSz && h[2*i] > h[swp])
                swp = 2*i;
            if(2*i + 1 <= heapSz && h[2*i+1] > h[swp])
                swp = 2*i + 1;
            if(swp == i)
                return;
            else
                swap(h[i], h[swp]), i = swp;
        }
    }

    int hSize()
    {
        return heapSz;
    }

    bool hEmpty()
    {
        return (heapSz == 0);
    }
};

// Testing
int main()
{
    heap H;
    H.init();

    int q, kom, x;
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d", &kom);
        if(kom == 1)
        {
            // insert
            scanf("%d", &x);
            H.push(x);
        }
        else if(kom == 2)
        {
            // peek
            printf("Max element: %d\n", H.top());
        }
        else if(kom == 3)
        {
            // pop
            H.pop();
        }
        else if(kom == 4)
        {
            // size
            printf("Heap size: %d\n", H.hSize());
        }
    }
    return  0;
}

/*
    #include <priority_queue>:

    struct cmp
    {
        bool operator()(const node a,const node b)
        const
        {
             return a.x<b.x;
        }
    };
    priority_queue<heapdata, vector<heapdata>, cmp> pq;
*/
