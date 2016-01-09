// RandomUsername (Nikola Jovanovic)
// MinStack + 2StackQueue
// push: O(1)
// pop: O(1)
// getFront: O(1)
// getTop: O(1)
// getMin: O(1)
// getSize: O(1)
// 2StackQueue - amortized constants

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

// minStack has an additional O(1) operation: find a minimal element currently on the stack
// DP: min[top..bot] = min(top, min[top+1..bot])
struct minStack
{
    stack<par> q;
    void push(int x)
    {
        if(q.empty())
            q.push( {x, x} );
        else
            q.push( {x, min(x, q.top().se)} );
    }
    void pop()
    {
        q.pop();
    }
    int getTop()
    {
        return q.top().fi;
    }
    int getMin()
    {
        return q.top().se;
    }
    int getSize()
    {
        return q.size();
    }
};

// A queue can be implemented using two stacks: inbox and outbox
struct twoStackQueue
{
    stack<int> in;
    stack<int> out;

    void flip()
    {
        // flip inbox
        while(!in.empty())
        {
            out.push( in.top() );
            in.pop();
        }
    }

    void push(int x)
    {
        in.push(x);
    }
    void pop()
    {
        if(out.empty())
            flip();
        if(!out.empty())
            out.pop();
    }
    int getFront()
    {
        if(out.empty())
            flip();
        if(!out.empty())
            return out.top();
        else
            return -1;
    }
    int getSize()
    {
        return in.size() + out.size();
    }
};

// These two structures can be combined to create a MinQueue

// Testing
int main()
{
    int q, kom, v;

    // tsq
    twoStackQueue tsq;
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d", &kom);
        if(kom == 1)
        {
            scanf("%d", &v);
            tsq.push(v);
        }
        else if(kom == 2)
        {
            tsq.pop();
        }
        else if(kom == 3)
        {
            printf("Front: %d\n", tsq.getFront());
        }
        else if(kom == 4)
        {
            printf("Size: %d\n",tsq.getSize());
        }
    }

    // ms
    minStack ms;
    scanf("%d", &q);
    while(q--)
    {
        scanf("%d", &kom);
        if(kom == 1)
        {
            scanf("%d", &v);
            ms.push(v);
        }
        else if(kom == 2)
        {
            ms.pop();
        }
        else if(kom == 3)
        {
            printf("Top: %d\n", ms.getTop());
        }
        else if(kom == 4)
        {
            printf("Size: %d\n",ms.getSize());
        }
        else if(kom == 5)
        {
            printf("Min: %d\n",ms.getMin());
        }
    }
    return 0;
}
