// RandomUsername (Nikola Jovanovic)
// Bignum Multiplication
// Mulitplying two 2N-digit numbers: O( N^1.585 )

#include <bits/stdc++.h>
#include <unistd.h>
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

using namespace std;

struct bignum
{
    int len;
    int dig[MAXN * 2];
    bignum()
    {
        len = 0;
        for(int i = 0; i < MAXN * 2; i++)
        {
            dig[i] = 0;
        }
    }
    bignum(char* digits) : bignum()
    {
        len = strlen(digits);
        for(int i = 0; i < len; i++)
        {
            dig[i] = digits[len - i - 1] - '0';
        }
    }
    void Print() 
    {
        for(int i = len - 1; i >= 0; i--)
        {
            printf("%d", dig[i]);
        }
        printf("\n");
    }
    int ToInt()
    {
        int ret = 0;
        for(int i = len - 1; i >= 0; i--)
        {
            ret = (ret * 10) + dig[i];
        }
        return ret;
    }
};

bignum Add(bignum a, bignum b)
{
    bignum c;
    c.len = max(a.len, b.len);
    int carry = 0;
    for(int i = 0; i < c.len; i++)
    {
        c.dig[i] = (a.dig[i] + b.dig[i] + carry) % 10;
        carry = (a.dig[i] + b.dig[i] + carry) / 10;
    }
    if(carry > 0)
    {
        c.dig[c.len++] = carry;
    }
    return c;
}

bignum Subtract(bignum a, bignum b)
{
    bignum c;
    for(int i = 0; i < a.len; i++)
    {
        if(a.dig[i] < b.dig[i])
        {
            a.dig[i] += 10;
            a.dig[i + 1]--;
        }
        c.dig[i] = a.dig[i] - b.dig[i];
        if(c.dig[i] != 0)
        {
            c.len = i + 1;
        }
    }
    return c;
}

bignum MulInt(bignum a, int b)
{
    bignum c;
    c.len = a.len;
    int carry = 0;
    for(int i = 0; i < a.len; i++)
    {
        c.dig[i] = (a.dig[i] * b + carry) % 10;
        carry = (a.dig[i] * b + carry) / 10;
    }
    while(carry > 0)
    {
        c.dig[c.len++] = carry % 10;
        carry /= 10;
    }
    return c;
}

bignum Shift(bignum a, int gap)
{
    bignum b;
    for(int i = a.len - 1 + gap; i >= 0; i--)
    {
        if(i < gap) 
        {
            b.dig[i] = 0;
        }
        else
        {
            b.dig[i] = a.dig[i - gap];
        }
    }
    b.len = a.len + gap;
    return b;
}

pair<bignum, bignum> Split(bignum a)
{
    bignum a0, a1;
    int n = (a.len + 1) / 2;
    for(int i = 0; i < a.len; i++)
    {
        if(i < n)
        {
            a0.dig[i] = a.dig[i];
        }
        else
        {
            a1.dig[i - n] = a.dig[i];
        }
    }
    a0.len = n;
    a1.len = a.len - n;
    return {a0, a1};
}

bignum NaiveMul(bignum a, bignum b)
{
    bignum ret;
    for(int i = b.len - 1; i >= 0; i--)
    {
        ret = Shift(ret, 1);
        ret = Add(ret, MulInt(a, b.dig[i])); 
    }
    return ret;
}

bignum DnqMul(bignum a, bignum b)
{
    a.len = b.len = max(a.len, b.len);
    if(a.len <= 8)
    {
        return MulInt(b, a.ToInt());
    }
    int n = (a.len + 1) / 2;
    bignum a0, a1, b0, b1;
    pair<bignum, bignum> a_split = Split(a);
    a0 = a_split.first, a1 = a_split.second;
    pair<bignum, bignum> b_split = Split(b);
    b0 = b_split.first, b1 = b_split.second;
    bignum a0b0 = DnqMul(a0, b0);
    bignum a1b1 = DnqMul(a1, b1);
    bignum inner = Subtract(Subtract(DnqMul(Add(a0, a1), Add(b0, b1)), a0b0), a1b1);
    bignum ret = Add(Add(a0b0, Shift(a1b1, 2 * n)), Shift(inner, n));
    return ret;
}

// Testing
int main()
{
    char pom[2 * MAXN];
    scanf("%s", pom);
    bignum a(pom);
    scanf("%s", pom);
    bignum b(pom);
    NaiveMul(a, b).Print();
    DnqMul(a, b).Print();
    return 0;
}
