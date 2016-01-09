// RandomUsername (Nikola Jovanovic)
// Matrix Operations
// Addition: O(ab) for Mab
// Substraction: O(ab) for Mab
// Scalar Multiplication: O(ab) for Mab
// Multiplication: O(abc) for Mab X Mbc

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

// Matrix class
struct matrix
{
    // The matrix and its dimensions
    int m[MAXN][MAXN];
    int r, c;

    // Empty constructor
    matrix()
    {

    }

    // Constructor that creates an empty matrix
    matrix(int r, int c)
    {
        this -> r = r;
        this -> c = c;
        for(int i = 1; i <= r; i++)
        {
            for(int j = 1; j <= c; j++)
            {
                m[i][j] = 0;
            }
        }
    }

    // Load a matrix from input
    void load()
    {
        scanf("%d %d", &r, &c);
        for(int i = 1; i <= r; i++)
        {
            for(int j = 1; j <= c; j++)
            {
                scanf("%d", &m[i][j]);
            }
        }
    }

    // Print a matrix
    void print()
    {
        printf("%dx%d:\n", r, c);
        for(int i = 1; i <= r; i++)
        {
            for(int j = 1; j <= c; j++)
            {
                printf("%d ", m[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    // Add two matrices of the same size
    matrix add(matrix b)
    {
        if(r != b.r || c != b.c)
        {
            printf("You can't add these matrices.");
            return matrix(1, 1);
        }
        matrix ret(r, c);
        for(int i = 1; i <= r; i++)
        {
            for(int j = 1; j <= c; j++)
            {
                ret.m[i][j] = m[i][j] + b.m[i][j];
            }
        }
        return ret;
    }

    // Subtract two matrices of the same size
    matrix subtract(matrix b)
    {
        if(r != b.r || c != b.c)
        {
            printf("You can't subtract these matrices.");
            return matrix(1, 1);
        }
        matrix ret(r, c);
        for(int i = 1; i <= r; i++)
        {
            for(int j = 1; j <= c; j++)
            {
                ret.m[i][j] = m[i][j] - b.m[i][j];
            }
        }
        return ret;
    }

    // Multiply a matrix with a scalar value
    matrix mulScalar(int k)
    {
        matrix ret(r, c);
        for(int i = 1; i <= r; i++)
        {
            for(int j = 1; j <= c; j++)
            {
                ret.m[i][j] = m[i][j] * k;
            }
        }
        return ret;
    }

    // Multiply two matrices a(i x k) and b(k x j)
    matrix mul(matrix b)
    {
        if(c != b.r)
        {
            printf("You can't multiply these matrices.");
            return matrix(1, 1);
        }
        matrix ret(r, b.c);
        for(int i = 1; i <= r; i++)
        {
            for(int j = 1; j <= b.c; j++)
            {
                for(int k = 1; k <= c; k++)
                {
                    ret.m[i][j] += m[i][k] * b.m[k][j];
                }
            }
        }
        return ret;
    }

};

// Testing
int main()
{
    matrix a, b;
    a.load();
    b.load();
    a.add(b).print();
    a.subtract(b).print();

    int k;
    scanf("%d", &k);
    a.mulScalar(k).print();

    matrix c;
    c.load();
    a.mul(c).print();
    b.mul(c).print();
    return 0;
}
