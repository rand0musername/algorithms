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
class BinaryHeap
{
    private:
        int h[MAXN];
        int heapSz;

        void siftUp(int i)
        {
            while(i > 1)
            {
                if(h[i] > h[i/2])
                    swap(h[i], h[i/2]), i /= 2;
                else
                    return;
            }
        }

        void siftDown(int i)
        {
            int swp;
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

        void heapifyUp()
        {
            for(int i = 1; i <= heapSz; i++)
            {
                siftUp(i);
            }
        }

        void heapifyDown()
        {
            for(int i = heapSz; i >= 1; i--)
            {
                siftDown(i);
            }
        }

    public:
        BinaryHeap()
        {
            this -> heapSz = 0;
        }

        BinaryHeap(vector<int> &v)
        {
            BinaryHeap();
            for(int num : v)
            {
                h[++heapSz] = num;
            }
            heapifyDown();
        }

        void push(int x)
        {
            h[++heapSz] = x;
            siftUp(heapSz);
        }

        void pop()
        {
            if(empty())
            {
                return;
            }
            swap(h[1], h[heapSz--]);
            siftDown(1);
        }

        int top()
        {
            if(empty())
            {
                return -1;
            }
            return h[1];
        }

        int size()
        {
            return heapSz;
        }

        bool empty()
        {
            return (heapSz == 0);
        }
};

// Testing
int main()
{
    BinaryHeap *H = new BinaryHeap();

    int kom;
    while(1)
    {
        printf("0 - init\n1 - push\n2 - top\n3 - pop\n4 - size\n");
        scanf("%d", &kom);
        if(kom == 0)
        {
            // heapify
            int n, num;
            vector<int> v;
            scanf("%d", &n);
            for(int i = 1; i <= n; i++)
            {
                scanf("%d", &num);
                v.push_back(num);
            }
            H = new BinaryHeap(v);
        }
        if(kom == 1)
        {
            // push
            int x;
            scanf("%d", &x);
            H -> push(x);
        }
        else if(kom == 2)
        {
            // top
            printf("Max element: %d\n", H -> top());
        }
        else if(kom == 3)
        {
            // pop
            H -> pop();
        }
        else if(kom == 4)
        {
            // size
            printf("Heap size: %d\n", H -> size());
        }
    }
    return  0;
}