// RandomUsername (Nikola Jovanovic)
// Heapsort
// Sorting an array: O( NlogN )
// N - array size

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

// Data Structures/Binary Heap.cpp
class BinaryHeap
{
    private:
        int h[MAXN];
        int heapSz;

        void siftUp(int i)
        {
            while(i > 1)
            {
                if(h[i] < h[i/2])
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
                if(2*i <= heapSz && h[2*i] < h[swp])
                    swp = 2*i;
                if(2*i + 1 <= heapSz && h[2*i+1] < h[swp])
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

// The array we're sorting and its size
int a[MAXN];
int n;

void heapSort()
{
    vector<int> v(a+1, a+n+1);
    BinaryHeap *H = new BinaryHeap(v);
    for(int i = 1; i <= n; i++)
    {
        a[i] = H -> top();
        H -> pop();
    }
}

// Testing
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    heapSort();
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
